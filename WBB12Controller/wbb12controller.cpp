#include "wbb12controller.h"

#include <QDebug>
#include <QSerialPort>
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

int WBB12Controller::WBB12_Input_Registers_Offset = 30001;
int WBB12Controller::WBB12_Holding_Registers_Offset = 40001;

int WBB12Controller::WBB12_NoError = 65535;
int WBB12Controller::WBB12_NoWarning = 65535;

signed short WBB12Controller::WFDE_TargetValue_NotAvailable = -32768;
signed short WBB12Controller::WFDE_TargetValue_Off = 0;

signed short WBB12Controller::WFDE_Temperature_NoSensor = -32768;
signed short WBB12Controller::WFDE_Temperature_NoValue = -32767;


WBB12Controller::WBB12Controller(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    connect(&m_statusTimer, &QTimer::timeout, this, &WBB12Controller::retrieveStatus);

    // inputs
    registerInput(WBB12_Input_Registers::OUTSIDE_TEMP_1, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::ERROR_CODE, WBB12_INTERVAL_WARNINGS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::WARNING_CODE, WBB12_INTERVAL_WARNINGS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::OPERATING_DISPLAY, WBB12_INTERVAL_MODES, QVariant::Int, WDF_OperationStatus);

    registerInput(WBB12_Input_Registers::HK1_ROOM_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK1_ROOM_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK1_FLOW_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK1_FLOW_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);

    /*
    registerInput(WBB12_Input_Registers::HK2_ROOM_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature, "hk2RoomTargetTemp");
    registerInput(WBB12_Input_Registers::HK2_ROOM_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature, "hk2RoomTemp");
    registerInput(WBB12_Input_Registers::HK2_FLOW_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature, "hk2FlowTargetTemp");
    registerInput(WBB12_Input_Registers::HK2_FLOW_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature, "hk2FlowTemp");
    */

    registerInput(WBB12_Input_Registers::HK3_ROOM_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK3_ROOM_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK3_FLOW_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HK3_FLOW_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);

    registerInput(WBB12_Input_Registers::WARM_WATER_TARGET_TEMP, WBB12_INTERVAL_FIXED_VALUES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::WARM_WATER_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);

    registerInput(WBB12_Input_Registers::HEAT_PUMP_MODE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_OperationStatus);
    registerInput(WBB12_Input_Registers::HEAT_PUMP_ERROR, WBB12_INTERVAL_WARNINGS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_PUMP_CONSUMPTION, 30000, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_PUMP_FLOW_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);
    registerInput(WBB12_Input_Registers::HEAT_PUMP_RETURN_FLOW_TEMP, WBB12_INTERVAL_TEMPERATURES, QVariant::Double, WDF_Temperature);

    registerInput(WBB12_Input_Registers::HEAT_COIL_STATUS, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_WORKING_HOURS, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_SWITCH, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_STATUS_COIL1, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_STATUS_COIL2, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_WORKING_HOURS_COIL1, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::HEAT_COIL_WORKING_HOURS_COIL2, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);

    registerInput(WBB12_Input_Registers::ENERGY_TOTAL_TODAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_TOTAL_YESTERDAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_TOTAL_MONTH, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_TOTAL_YEAR, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);

    registerInput(WBB12_Input_Registers::ENERGY_HEATING_TODAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_HEATING_YESTERDAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_HEATING_MONTH, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_HEATING_YEAR, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);

    registerInput(WBB12_Input_Registers::ENERGY_WARM_WATER_TODAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_WARM_WATER_YESTERDAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_WARM_WATER_MONTH, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_WARM_WATER_YEAR, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);

    registerInput(WBB12_Input_Registers::ENERGY_COOLING_TODAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_COOLING_YESTERDAY, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_COOLING_MONTH, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);
    registerInput(WBB12_Input_Registers::ENERGY_COOLING_YEAR, WBB12_INTERVAL_STATISTICS, QVariant::Int, WDF_Count);

    // holdings
    registerHolding(WBB12_Holding_Registers::OPERATING_MODE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_OperationStatus);

    registerHolding(WBB12_Holding_Registers::HK1_HEATING_CONFIG, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_DEMAND_TYPE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_OPERATING_MODE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_PAUSE_PARTY, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);

    registerHolding(WBB12_Holding_Registers::HK1_HEATING_TARGET_TEMP_COMFORT, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_TARGET_TEMP_NORMAL, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_TARGET_TEMP_REDUCE, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_HEAD_CURVE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_SUMMER_WINTER_SWITCH, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_CONSTANT_TEMP, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_HEATING_CONSTANT_TEMP_REDUCE, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK1_COOLING_CONSTANT_TEMP, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);

    registerHolding(WBB12_Holding_Registers::HK3_HEATING_CONFIG, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_DEMAND_TYPE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_OPERATING_MODE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_PAUSE_PARTY, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_TARGET_TEMP_COMFORT, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_TARGET_TEMP_NORMAL, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_TARGET_TEMP_REDUCE, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_HEAD_CURVE, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_SUMMER_WINTER_SWITCH, WBB12_INTERVAL_MODES, QVariant::Int, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_CONSTANT_TEMP, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_HEATING_CONSTANT_TEMP_REDUCE, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HK3_COOLING_CONSTANT_TEMP, WBB12_INTERVAL_MODES, QVariant::Double, WDF_Temperature);

    registerHolding(WBB12_Holding_Registers::WARM_WATER_CONFIG, WBB12_INTERVAL_MODES,                   QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::WARM_WATER_PUSH, WBB12_INTERVAL_MODES,                     QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::WARM_WATER_NORMAL, WBB12_INTERVAL_MODES,                   QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::WARM_WATER_REDUCE, WBB12_INTERVAL_MODES,                   QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::WARM_WATER_SG_READY, WBB12_INTERVAL_MODES,                 QVariant::Double, WDF_Temperature);

    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_CONFIG, WBB12_INTERVAL_MODES,                    QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_ACTIVATION_MODE, WBB12_INTERVAL_MODES,           QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_HEATING, WBB12_INTERVAL_MODES,                   QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_COOLING, WBB12_INTERVAL_MODES,                   QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_WARM_WATER, WBB12_INTERVAL_MODES,                QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_DEICE, WBB12_INTERVAL_MODES,                     QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_VOLUME_FLOW_HEATING, WBB12_INTERVAL_MODES,       QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_VOLUME_FLOW_COOLING, WBB12_INTERVAL_MODES,       QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_PUMP_VOLUME_FLOW_WARM_WATER, WBB12_INTERVAL_MODES,    QVariant::Int, WDF_Count);

    registerHolding(WBB12_Holding_Registers::HEAT_COIL_CONFIG, WBB12_INTERVAL_MODES,                    QVariant::Int, WDF_Count);
    registerHolding(WBB12_Holding_Registers::HEAT_COIL_BORDER_TEMP, WBB12_INTERVAL_TEMPERATURES,        QVariant::Double, WDF_Temperature);
    registerHolding(WBB12_Holding_Registers::HEAT_COIL_BIVALENT_TEMP, WBB12_INTERVAL_TEMPERATURES,      QVariant::Double, WDF_Temperature_Int);
    registerHolding(WBB12_Holding_Registers::HEAT_COIL_BIVALENT_TEMP_WW, WBB12_INTERVAL_TEMPERATURES,   QVariant::Double, WDF_Temperature_Int);
}

void WBB12Controller::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));

    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_modbusClient.setConnectionParameter(QModbusDevice::NetworkAddressParameter, m_config->getString(this, "tcp.ip", "127.0.0.1"));
    m_modbusClient.setConnectionParameter(QModbusDevice::NetworkPortParameter, m_config->getString(this, "tcp.port", "502"));
    m_modbusClient.setTimeout(500);
    m_modbusClient.setNumberOfRetries(1);

    connect(&m_modbusClient, &QModbusDevice::stateChanged, this, &WBB12Controller::onStateChanged);
    connect(&m_modbusClient, &QModbusDevice::errorOccurred, this, &WBB12Controller::onErrorOccurred);
}

void WBB12Controller::start() {
    iDebug() << Q_FUNC_INFO;

    m_modbusClient.connectDevice();
}

void WBB12Controller::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}

void WBB12Controller::bindValueManager(ValueManagerBase* valueManager, ActorManager *actorManager, DatamodelBase* datamodel) {
    iDebug() << Q_FUNC_INFO;

    m_valueManager = valueManager;
    m_actorManager = actorManager;

    iInfo() << "Getting value group" << this->id();
    m_wbb12Group = datamodel->valueGroup(this->id());
    Q_ASSERT(m_wbb12Group != nullptr);

    for (WBB12_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue retVal = m_inputRegisters.value(reg);

        ValueBase* val = m_valueManager->getValue(m_wbb12Group, retVal.mqttName);
        if (val == nullptr) {
            iWarning() << "Value not in datamodel" << retVal.mqttName;
            Q_ASSERT(val != nullptr);
        }

        m_inputMappings.insert(reg, val);
    }

    for (WBB12_Holding_Registers reg : m_holdingRegisters.keys()) {
        RetrieveValue retVal = m_holdingRegisters.value(reg);

        ValueBase* val = m_actorManager->getActor(m_wbb12Group, retVal.mqttName);
        if (val == nullptr) {
            // try to find in value
            val = m_valueManager->getValue(m_wbb12Group, retVal.mqttName);
            if (val == nullptr) {
                iWarning() << "Unable to find actor or value" << retVal.mqttName;
                Q_ASSERT(val != nullptr);
            }
        } else {
            ValueActor* actor = static_cast<ValueActor*>(val);
            Helpers::safeConnect(actor, &ValueActor::requestSetValue, this, &WBB12Controller::onRequestSetValue, SIGNAL(requestSetValue()), SLOT(onRequestSetValue()));
        }

        m_holdingMappings.insert(reg, val);
    }
}

void WBB12Controller::onRequestSetValue() {
    iDebug() << Q_FUNC_INFO;

    ValueActor* actor = static_cast<ValueActor*>(sender());

    WBB12_Holding_Registers reg = getHolding(actor->id());
    RetrieveValue retVal = m_holdingRegisters.value(reg);

    if (retVal.type != QVariant::Invalid) {
        _writeHolding(reg, retVal, actor->rawValue());
    } else {
        iWarning() << "Unable to resolve" << actor->id();
    }
}

void WBB12Controller::onStateChanged() {
    iDebug() << Q_FUNC_INFO;

    switch(m_modbusClient.state()) {
    case QModbusClient::ConnectedState:
        m_statusTimer.start();
        Q_EMIT(controllerConnected());

        /*
        _writeHolding(HK1_HEATING_PAUSE_PARTY, m_holdingRegisters.value(HK1_HEATING_PAUSE_PARTY), 4);
        QThread::msleep(100);
        QThread::yieldCurrentThread();
        _writeHolding(HK3_HEATING_PAUSE_PARTY, m_holdingRegisters.value(HK3_HEATING_PAUSE_PARTY), 4);
        */
        //_writeHolding(OPERATING_MODE, m_holdingRegisters.value(OPERATING_MODE), 4);     // standby

        break;
    case QModbusClient::UnconnectedState:
        m_statusTimer.stop();
        Q_EMIT(controllerDisconnected());
        break;
    default:
        iDebug() << m_modbusClient.state();
        break;
    }
}

void WBB12Controller::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

WBB12Controller::WBB12_Holding_Registers WBB12Controller::getHolding(QString name) {
    QString enumName;

    QRegExp ex("(?=[A-Z]+)");
    ex.setCaseSensitivity(Qt::CaseSensitive);

    for (QString token : name.split(ex)) {
        enumName.append(token.toUpper());
        enumName.append("_");
    }

    if (enumName.endsWith("_")) {
        enumName.chop(1);
    }

    return static_cast<WBB12_Holding_Registers>(QMetaEnum::fromType<WBB12_Holding_Registers>().keyToValue(enumName.toLatin1()));
}

void WBB12Controller::registerInput(WBB12_Input_Registers reg, qint64 retrieveInterval, QVariant::Type type, WBB12_DataFormat dataFormat) {
    iDebug() << Q_FUNC_INFO << reg;

    RetrieveValue val;

    val.retrieveInterval = retrieveInterval;
    val.type = type;
    val.dataFormat = dataFormat;
    val.mqttName = Helpers::generateMqttNameFromConstant(QVariant::fromValue(reg).toString());
    iDebug() << Q_FUNC_INFO << reg << "->" << val.mqttName;

    m_inputRegisters.insert(reg, val);
    m_lastInputReadings.insert(reg, 0);
}

void WBB12Controller::registerHolding(WBB12_Holding_Registers reg, qint64 retrieveInterval, QVariant::Type type, WBB12_DataFormat dataFormat) {
    iDebug() << Q_FUNC_INFO << reg;

    RetrieveValue val;

    val.retrieveInterval = retrieveInterval;
    val.type = type;
    val.dataFormat = dataFormat;
    val.mqttName = Helpers::generateMqttNameFromConstant(QVariant::fromValue(reg).toString());

    m_holdingRegisters.insert(reg, val);
    m_lastHoldingReadings.insert(reg, 0);
}

void WBB12Controller::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    for (WBB12_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue val = m_inputRegisters.value(reg);

        if (QDateTime::currentMSecsSinceEpoch() - m_lastInputReadings.value(reg) >= val.retrieveInterval) {
            _readInput(reg, val);
        } else {
            iDebug() << "Skipping" << reg;
        }

        QThread::msleep(100);
        QThread::yieldCurrentThread();
    }

    for (WBB12_Holding_Registers reg : m_holdingRegisters.keys()) {
        RetrieveValue val = m_holdingRegisters.value(reg);

        if (QDateTime::currentMSecsSinceEpoch() - m_lastHoldingReadings.value(reg) >= val.retrieveInterval) {
            _readHolding(reg, val);
        } else {
            iDebug() << "Skipping" << reg;
        }

        QThread::msleep(100);
        QThread::yieldCurrentThread();
    }
}

void WBB12Controller::_readInput(WBB12_Input_Registers reg, RetrieveValue val) {
    QModbusDataUnit dataUnit(QModbusDataUnit::InputRegisters, WBB12_Input_Registers_Offset + reg, 1);

    QModbusReply* reply = m_modbusClient.sendReadRequest(dataUnit, m_slaveId);
    connect(reply, &QModbusReply::finished, [this, reply, reg, val] {

        if (reply->error() == QModbusDevice::NoError) {
            QVariant value = parseValue(reply->result().value(0), val.dataFormat);
            iDebug() << reg << value;
            ValueBase *v = m_inputMappings.value(reg);
            m_valueManager->updateAndPublishValue(v, value);
            m_lastInputReadings.insert(reg, QDateTime::currentMSecsSinceEpoch());
        } else if (reply->error() == QModbusDevice::ProtocolError) {
            iWarning() << "Modbus error" << reply->error();
        } else {
            iWarning() << "Modbus error" << reply->error();
        }
        reply->deleteLater();
    });
}

void WBB12Controller::_readHolding(WBB12_Holding_Registers reg, RetrieveValue val) {
    QModbusDataUnit dataUnit(QModbusDataUnit::HoldingRegisters, WBB12_Holding_Registers_Offset + reg, 1);

    QModbusReply* reply = m_modbusClient.sendReadRequest(dataUnit, m_slaveId);
    connect(reply, &QModbusReply::finished, [this, reply, reg, val] {
        if (reply->error() == QModbusDevice::NoError) {
            QVariant value = parseValue(reply->result().value(0), val.dataFormat);
            iDebug() << reg << value;
            ValueBase *v = m_holdingMappings.value(reg);
            m_valueManager->updateAndPublishValue(v, value);
            m_lastHoldingReadings.insert(reg, QDateTime::currentMSecsSinceEpoch());
        } else if (reply->error() == QModbusDevice::ProtocolError) {
            iWarning() << "Modbus error" << reply->error();
        } else {
            iWarning() << "Modbus error" << reply->error();
        }
        reply->deleteLater();
    });
}

void WBB12Controller::_writeHolding(WBB12_Holding_Registers reg, RetrieveValue val, QVariant value) {
    iDebug() << Q_FUNC_INFO << reg;

    QModbusDataUnit dataUnit(QModbusDataUnit::HoldingRegisters, WBB12_Holding_Registers_Offset + reg, 1);
    dataUnit.setValueCount(1);
    dataUnit.setValue(0, generateValue(value, val.dataFormat));

    QModbusReply* reply = m_modbusClient.sendWriteRequest(dataUnit, m_slaveId);
    connect(reply, &QModbusReply::finished, [this, reply, reg, val] {

        if (reply->error() == QModbusDevice::NoError) {
            QVariant value = parseValue(reply->result().value(0), val.dataFormat);
            iDebug() << reg << value;
            ValueBase *v = m_holdingMappings.value(reg);
            m_valueManager->updateAndPublishValue(v, value);
            m_lastHoldingReadings.insert(reg, QDateTime::currentMSecsSinceEpoch());
        } else if (reply->error() == QModbusDevice::ProtocolError) {
            iWarning() << "Modbus error" << reply->error();
        } else {
            iWarning() << "Modbus error" << reply->error();
        }
        reply->deleteLater();
    });
}

QVariant WBB12Controller::parseValue(int rawValue, WBB12_DataFormat format) {
    switch(format) {
    case WDF_TargetValue: {
        signed short shortVal = (signed short) rawValue;
        if (shortVal == WFDE_TargetValue_NotAvailable || shortVal == WFDE_TargetValue_Off) {
            return shortVal;
        } else {
            double doubleVal = shortVal;
            doubleVal /= 10;
            return doubleVal;
        }
    }
    case WDF_Temperature: {
        signed short shortVal = (signed short) rawValue;
        if (shortVal == WFDE_Temperature_NoSensor || shortVal == WFDE_Temperature_NoValue) {
            return shortVal;
        } else {
            double doubleVal = shortVal;
            doubleVal /= 10;
            return doubleVal;
        }
    }
    case WDF_ConfigHP:
    case WDF_ConfigHeating:
    case WDF_StatusHeating:
    case WDF_AllowanceStatusHP:
    case WDF_ConfigWarmWater:
    case WDF_StatusWarmWater:
    case WDF_EEZOperationStatus:
    case WDF_Warning:
    case WDF_Blocking:
    case WDF_Locking:
    case WDF_Status:
    case WDF_ConfigRoom:
        return (unsigned char) rawValue;
    case WDF_Temperature_Int:
    case WDF_Count:
    case WDF_Version:
    case WDF_OperationStatus:
        return (unsigned short) rawValue;
    default:
        return rawValue;
    }
}

quint16 WBB12Controller::generateValue(QVariant val, WBB12_DataFormat format) {
    switch(format) {
    case WDF_TargetValue: {
        /*
        signed short shortVal = (signed short) rawValue;
        if (shortVal == WFDE_TargetValue_NotAvailable || shortVal == WFDE_TargetValue_Off) {
            return shortVal;
        } else {
            double doubleVal = shortVal;
            doubleVal /= 10;
            return doubleVal;
        }
    }
    */
    case WDF_Temperature: {
        double doubleVal = val.toDouble();
        signed short shortVal = doubleVal * 10;
        return shortVal;
    }
    }
    case WDF_ConfigHP:
    case WDF_ConfigHeating:
    case WDF_StatusHeating:
    case WDF_AllowanceStatusHP:
    case WDF_ConfigWarmWater:
    case WDF_StatusWarmWater:
    case WDF_EEZOperationStatus:
    case WDF_Warning:
    case WDF_Blocking:
    case WDF_Locking:
    case WDF_Status:
    case WDF_ConfigRoom:
    case WDF_Count:
    case WDF_Version:
    case WDF_OperationStatus:
        //return (unsigned short) rawValue;
    default: ;
        //return rawValue;
    }
    return (quint16) val.toUInt();
}

