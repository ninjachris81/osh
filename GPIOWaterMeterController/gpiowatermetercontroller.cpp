#include "gpiowatermetercontroller.h"

#include <QDebug>
#include <QDateTime>
#include <QThread>

#include "controller/controllermanager.h"
#include "helpers.h"
#include "qmetaobject.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"
#include "value/doublevalue.h"
#include "value/integervalue.h"
#include "actor/valueactor.h"

GPIOWaterMeterController::GPIOWaterMeterController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    //connect(&m_statusTimer, &QTimer::timeout, this, &RS232WaterMeterController::retrieveStatus);
    connect(m_debounceReader, &MCPDebounceReader::stateChanged, this, &GPIOWaterMeterController::onStateChanged);
}

void GPIOWaterMeterController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    //m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));

    m_sensorCount = m_config->getInt(this, "inputCount", 4);
    m_dataOffset = m_config->getInt(this, "sensoroffset", 9);
    m_stepAmountML = m_config->getInt(this, "stepMl", 250);

    int pinBase = m_config->getInt(this, "mcp.pinBase", 64);
    int addr = m_config->getInt(this, "mcp.addr", 0x20);


    m_debounceReader = new MCPDebounceReader(m_sensorCount, addr, pinBase);
}

void GPIOWaterMeterController::start() {
    iDebug() << Q_FUNC_INFO;

    m_debounceReader->start();
}

void GPIOWaterMeterController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void GPIOWaterMeterController::bindValueManager(ClientValueManager* valueManager, DatamodelBase* datamodel) {
    iDebug() << Q_FUNC_INFO;

    m_valueManager = valueManager;

    iInfo() << "Getting value group" << this->id();
    m_valueGroup = datamodel->valueGroup(this->id());
    Q_ASSERT(m_valueGroup != nullptr);

    for (uint8_t i = 0; i<m_sensorCount;i++) {
        DoubleValue* val = static_cast<DoubleValue*>(m_valueManager->getValue(m_valueGroup, QString::number(i)));
        if (val == nullptr) {
            iWarning() << "Value not in datamodel" << i;
            Q_ASSERT(val != nullptr);
        } else if (val->rawValue().isNull()) {
            val->updateValue(0.0, false);
        }

        m_valueMappings.append(val);

        valueManager->registerForNotification(val);
    }
}

void GPIOWaterMeterController::onStateChanged(quint8 index, bool state) {
    iDebug() << Q_FUNC_INFO << index << state;
    increaseWaterLevel(index);
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

DoubleValue* GPIOWaterMeterController::getValue(uint8_t id) {
    if (id < m_sensorCount + m_dataOffset) {
        DoubleValue* val = m_valueMappings.at(id - m_dataOffset);
        Q_ASSERT(val != nullptr);
        return val;
    } else {
        iWarning() << "Invalid id" << id;
    }

    return nullptr;
}

void GPIOWaterMeterController::increaseWaterLevel(uint8_t id) {
    iDebug() << Q_FUNC_INFO << id;

    DoubleValue* val = getValue(id);

    if (val != nullptr) {
        val->updateValue(val->rawValue().toDouble() + (m_stepAmountML / 1000), true);
        m_valueManager->publishValue(val);
    }
}
