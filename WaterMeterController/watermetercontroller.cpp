#include "watermetercontroller.h"

#include <QDebug>
#include <QDateTime>
#include <QThread>

#include "controller/controllermanager.h"
#include "helpers.h"
#include "qmetaobject.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"
#include "shared/mqtt_qt.h"
#include "value/doublevalue.h"
#include "value/integervalue.h"
#include "actor/valueactor.h"
#include "datamodel/datamodelmanager.h"
#include "communication/mqtt/mqttcommunicationmanagerbase.h"

WaterMeterController::WaterMeterController(ControllerManager *manager, QString id, QString inputSensorGroupId, QString waterFlowValueGroupId, QString waterLevelValueGroupId, QObject *parent) : ControllerBase(manager, id, parent), 
m_inputSensorGroupId(inputSensorGroupId), m_waterFlowValueGroupId(waterFlowValueGroupId), m_waterLevelValueGroupId(waterLevelValueGroupId)
{
    connect(&m_flowTimer, &QTimer::timeout, this, &WaterMeterController::onCalculateFlow);
}

void WaterMeterController::init(){
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ClientValueManager);
    ClientValueManager *valueManager = m_manager->getManager<ClientValueManager>(ClientValueManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, DatamodelManager);
    DatamodelManager *datamodelManager = m_manager->getManager<DatamodelManager>(DatamodelManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, MqttCommunicationManagerBase);
    MqttCommunicationManagerBase *commManager = m_manager->getManager<MqttCommunicationManagerBase>(MqttCommunicationManagerBase::MANAGER_ID);

    commManager->setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);
    commManager->setCustomValueGroups(QStringList() <<  m_inputSensorGroupId << m_waterLevelValueGroupId << m_waterFlowValueGroupId);

    //m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));

    m_inputSensorCount = m_config->getInt(this, "inputSensorCount", 4);

    m_inputSensorOffset = m_config->getInt(this, "inputSensorOffset", 0);
    m_waterLevelOffset = m_config->getInt(this, "waterLevelOffset", 0);
    m_waterFlowOffset = m_config->getInt(this, "waterFlowOffset", 0);
    m_stepAmountML = m_config->getInt(this, "stepMl", 250);

    m_flowTimer.setInterval(3000);

    m_startedAtMs = QDateTime::currentMSecsSinceEpoch();

    m_waterFlows.clear();
}

void WaterMeterController::start() {
    iDebug() << Q_FUNC_INFO;

    m_flowTimer.start();
}

void WaterMeterController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void WaterMeterController::bindValueManager(ClientValueManager* valueManager, DatamodelBase* datamodel) {
    iDebug() << Q_FUNC_INFO;

    m_valueManager = valueManager;

    iInfo() << "Getting value group" << m_inputSensorGroupId;
    m_inputSensorGroup = datamodel->valueGroup(m_inputSensorGroupId);
    Q_ASSERT(m_inputSensorGroup != nullptr);

    iInfo() << "Getting value group" << m_waterFlowValueGroupId;
    m_waterFlowValueGroup = datamodel->valueGroup(m_waterFlowValueGroupId);
    Q_ASSERT(m_waterFlowValueGroup != nullptr);

    iInfo() << "Getting value group" << m_waterLevelValueGroupId;
    m_waterLevelValueGroup = datamodel->valueGroup(m_waterLevelValueGroupId);
    Q_ASSERT(m_waterLevelValueGroup != nullptr);

    for (quint8 i = 0; i<m_inputSensorCount;i++) {
        BooleanValue* inputSensor = static_cast<BooleanValue*>(m_valueManager->getValue(m_inputSensorGroup, QString::number(i + m_inputSensorOffset)));
        DoubleValue* waterFlow = static_cast<DoubleValue*>(m_valueManager->getValue(m_waterFlowValueGroup, QString::number(i + m_waterFlowOffset)));
        DoubleValue* waterLevel = static_cast<DoubleValue*>(m_valueManager->getValue(m_waterLevelValueGroup, QString::number(i + m_waterLevelOffset)));
        if (inputSensor == nullptr || waterFlow == nullptr || waterLevel == nullptr) {
            iWarning() << "Value not in datamodel" << i << inputSensor << waterFlow << waterLevel;
            Q_ASSERT(inputSensor != nullptr);
            Q_ASSERT(waterFlow != nullptr);
            Q_ASSERT(waterLevel != nullptr);
        }

        waterLevel->withAlwaysEmit(true);
        inputSensor->withAlwaysEmit(false);

        m_inputSensorMappings.append(inputSensor);
        m_waterFlowMappings.append(waterFlow);
        m_waterLevelMappings.append(waterLevel);
        m_waterLevelInitialized.append(false);

        valueManager->registerForNotification(inputSensor);
        valueManager->registerForNotification(waterFlow);
        valueManager->registerForNotification(waterLevel);

        connect(inputSensor, &BooleanValue::valueChanged, this, [this, i]() {
            onStateChanged(i, static_cast<BooleanValue*>(sender())->rawValue().toBool());
        });

        connect(waterLevel, &DoubleValue::valueChanged, this, [this, i]() {
            iDebug() << "Water level changed" << i << static_cast<DoubleValue*>(sender())->rawValue();
            m_waterLevelInitialized[i] = true;
        });

        m_waterFlows.append(0);
    }
}

void WaterMeterController::onStateChanged(quint8 index, bool state) {
    iInfo() << Q_FUNC_INFO << index << state;

    if (!m_waterLevelInitialized[index] && QDateTime::currentMSecsSinceEpoch() - m_startedAtMs < m_initialLevelTimeoutMs) {
        iWarning() << "Water level not initialized yet - ignoring input";
        return;
    }

    DoubleValue* waterLevel = m_waterLevelMappings.value(index);

    if (waterLevel != nullptr) {
        if (waterLevel->rawValue().isNull()) {
            iWarning() << "No initial water level - assuming 0";
            waterLevel->updateValue(0.0, false);
        } else {
            iInfo() << "Resuming at water level" << waterLevel->rawValue();
        }

        waterLevel->updateValue(waterLevel->rawValue().toDouble() + (m_stepAmountML / 1000 / 2), true);
        m_valueManager->publishValue(waterLevel);
    }

    m_flowCounterMutex.lock();
    m_waterFlows[index]++;
    m_flowCounterMutex.unlock();
}

void WaterMeterController::onCalculateFlow() {
    m_flowCounterMutex.lock();

    float buff[m_inputSensorCount];      // as L/min

    for (quint8 i = 0; i<m_inputSensorCount;i++) {
        buff[i] = (m_stepAmountML * m_waterFlows[i] / 1000 / 2) * 20;       // 20 = 60 / interval
        m_waterFlows[i] = 0;
    }

    m_flowCounterMutex.unlock();

    for (quint8 i = 0; i<m_inputSensorCount;i++) {
        DoubleValue* waterFlow = m_waterFlowMappings.value(i);

        iDebug() << i << buff[i];

        if (waterFlow->updateValue(buff[i], false)) {
            m_valueManager->publishValue(waterFlow);
        }
    }

}
