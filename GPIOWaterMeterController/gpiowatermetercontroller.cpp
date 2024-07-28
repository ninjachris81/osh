#include "gpiowatermetercontroller.h"

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
#include "communication/mqtt/mqttcommunicationmanagerbase.h"

GPIOWaterMeterController::GPIOWaterMeterController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    //connect(&m_statusTimer, &QTimer::timeout, this, &RS232WaterMeterController::retrieveStatus);
    connect(&m_flowTimer, &QTimer::timeout, this, &GPIOWaterMeterController::onCalculateFlow);
}

void GPIOWaterMeterController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, MqttCommunicationManagerBase);
    MqttCommunicationManagerBase *commManager = m_manager->getManager<MqttCommunicationManagerBase>(MqttCommunicationManagerBase::MANAGER_ID);

    m_waterLevelValueGroupId = m_config->getString(this, "waterLevelValueGroupId", m_id);
    m_waterFlowValueGroupId = m_config->getString(this, "waterFlowValueGroupId", m_id);

    commManager->setCustomChannels(QStringList() << MQTT_MESSAGE_TYPE_ST);
    commManager->setCustomValueGroups(QStringList() << m_waterLevelValueGroupId << m_waterFlowValueGroupId);

    //m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));

    m_sensorCount = m_config->getInt(this, "inputCount", 4);
    m_dataOffset = m_config->getInt(this, "inputOffset", 0);
    m_stepAmountML = m_config->getInt(this, "stepMl", 250);

    int pinBase = m_config->getInt(this, "mcp.pinBase", 64);
    int addr = m_config->getInt(this, "mcp.addr", 0x20);

    m_debounceReader = new MCPDebounceReader(m_sensorCount, addr, pinBase);
    connect(m_debounceReader, &MCPDebounceReader::stateChanged, this, &GPIOWaterMeterController::onStateChanged);

    m_flowTimer.setInterval(4000);

    m_waterFlows.clear();
}

void GPIOWaterMeterController::start() {
    iDebug() << Q_FUNC_INFO;

    m_debounceReader->start();
    m_flowTimer.start();
}

void GPIOWaterMeterController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void GPIOWaterMeterController::bindValueManager(ClientValueManager* valueManager, DatamodelBase* datamodel) {
    iDebug() << Q_FUNC_INFO;

    m_valueManager = valueManager;

    iInfo() << "Getting value group" << m_waterFlowValueGroupId;
    m_waterFlowValueGroup = datamodel->valueGroup(m_waterFlowValueGroupId);
    Q_ASSERT(m_waterFlowValueGroup != nullptr);

    iInfo() << "Getting value group" << m_waterLevelValueGroupId;
    m_waterLevelValueGroup = datamodel->valueGroup(m_waterLevelValueGroupId);
    Q_ASSERT(m_waterLevelValueGroup != nullptr);

    for (quint8 i = 0; i<m_sensorCount;i++) {
        DoubleValue* waterFlow = static_cast<DoubleValue*>(m_valueManager->getValue(m_waterFlowValueGroup, QString::number(i + m_dataOffset)));
        DoubleValue* waterLevel = static_cast<DoubleValue*>(m_valueManager->getValue(m_waterLevelValueGroup, QString::number(i + m_dataOffset)));
        if (waterFlow == nullptr || waterLevel == nullptr) {
            iWarning() << "Value not in datamodel" << i << waterFlow << waterLevel;
            Q_ASSERT(waterFlow != nullptr);
            Q_ASSERT(waterLevel != nullptr);
        } else {
            if (waterFlow->rawValue().isNull()) waterFlow->updateValue(0.0, false);
            if (waterLevel->rawValue().isNull()) waterLevel->updateValue(0.0, false);
        }

        m_waterFlowMappings.append(waterFlow);
        m_waterLevelMappings.append(waterLevel);

        valueManager->registerForNotification(waterFlow);
        valueManager->registerForNotification(waterLevel);

        m_waterFlows.append(0);
    }
}

void GPIOWaterMeterController::onStateChanged(quint8 index, bool state) {
    iDebug() << Q_FUNC_INFO << index << state;

    DoubleValue* waterLevel = m_waterLevelMappings.value(index);

    if (waterLevel != nullptr) {
        waterLevel->updateValue(waterLevel->rawValue().toDouble() + (m_stepAmountML / 1000), true);
        m_valueManager->publishValue(waterLevel);
    }

    m_flowCounterMutex.lock();
    m_waterFlows[index]++;
    m_flowCounterMutex.unlock();
}

void GPIOWaterMeterController::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected", QtCriticalMsg);
    //m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}



void GPIOWaterMeterController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

}


void GPIOWaterMeterController::onCalculateFlow() {
    m_flowCounterMutex.lock();

    float buff[m_sensorCount];

    for (quint8 i = 0; i<m_sensorCount;i++) {
        buff[i] = m_stepAmountML * m_waterFlows[i] / 1000;
        m_waterFlows[i] = 0;
    }

    m_flowCounterMutex.unlock();

    for (quint8 i = 0; i<m_sensorCount;i++) {
        DoubleValue* waterLevel = m_waterLevelMappings.value(i);

        if (waterLevel->updateValue(buff[i], false)) {
            m_valueManager->publishValue(waterLevel);
        }
    }

}
