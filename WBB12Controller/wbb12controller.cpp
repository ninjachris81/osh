#include "wbb12controller.h"

#include <QDebug>
#include <QSerialPort>

#include "controller/controllermanager.h"
#include "shared/controllercmdtypes_qt.h"
#include "controller/controllermessage.h"
#include "value/booleanvalue.h"
#include "value/doublevalue.h"
#include "value/integervalue.h"

int WBB12Controller::WBB12_Input_Registers_Offset = 30001;

signed short WBB12Controller::WFDE_TargetValue_NotAvailable = -32768;
signed short WBB12Controller::WFDE_TargetValue_Off = 0;

signed short WBB12Controller::WFDE_Temperature_NoSensor = -32768;
signed short WBB12Controller::WFDE_Temperature_NoValue = -32767;


WBB12Controller::WBB12Controller(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    connect(&m_statusTimer, &QTimer::timeout, this, &WBB12Controller::retrieveStatus);

    registerInput(WBB12_Input_Registers::OUTSIDE_TEMP_1, 60000, QVariant::Double, WDF_Temperature, "outsideTemp1");
    registerInput(WBB12_Input_Registers::OPERATING_DISPLAY, 120000, QVariant::Int, WDF_OperationStatus, "operationStatus");

    registerInput(WBB12_Input_Registers::HK1_ROOM_TARGET_TEMP, 60000, QVariant::Double, WDF_Temperature, "hk1RoomTargetTemp1");
    registerInput(WBB12_Input_Registers::HK1_ROOM_TEMP, 60000, QVariant::Double, WDF_Temperature, "hk1RoomTemp1");
}

void WBB12Controller::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

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

void WBB12Controller::bindValueManager(ValueManagerBase* valueManager) {
    iDebug() << Q_FUNC_INFO;

    m_valueManager = valueManager;

    ValueGroup wbb12Group(m_id);

    for (WBB12_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue retVal = m_inputRegisters.value(reg);
        ValueBase *val;

        switch(retVal.type) {
        case QVariant::Int:
            val = new IntegerValue(&wbb12Group, retVal.mqttName, value::VALTYPE_HEAT_PUMP_DATA);
            break;
        case QVariant::Double:
            val = new DoubleValue(&wbb12Group, retVal.mqttName, value::VALTYPE_HEAT_PUMP_DATA);
            break;
        case QVariant::Bool:
            val = new BooleanValue(&wbb12Group, retVal.mqttName, value::VALTYPE_HEAT_PUMP_DATA);
            break;
        default:
            qFatal("Invalid type");
        }

        m_valueManager->registerValue(val);
        m_valueMappings.insert(reg, val);
    }

}

void WBB12Controller::onStateChanged() {
    iDebug() << Q_FUNC_INFO;

    switch(m_modbusClient.state()) {
    case QModbusClient::ConnectedState:
        m_statusTimer.start();
        Q_EMIT(controllerConnected());
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

void WBB12Controller::registerInput(WBB12_Input_Registers reg, uint16_t retrieveInterval, QVariant::Type type, WBB12_DataFormat dataFormat, QString mqttName) {
    iDebug() << Q_FUNC_INFO << reg;

    RetrieveValue val;

    val.retrieveInterval = retrieveInterval;
    val.type = type;
    val.dataFormat = dataFormat;
    val.mqttName = mqttName;

    m_inputRegisters.insert(reg, val);
}


void WBB12Controller::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    for (WBB12_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue val = m_inputRegisters.value(reg);

        _readInput(reg, val);
    }
}

void WBB12Controller::_readInput(WBB12_Input_Registers reg, RetrieveValue val) {
    QModbusDataUnit dataUnit(QModbusDataUnit::InputRegisters, WBB12_Input_Registers_Offset + reg, 1);

    QModbusReply* reply = m_modbusClient.sendReadRequest(dataUnit, m_slaveId);
    //QModbusReply* reply = m_modbusClient.sendRawRequest(req, m_slaveId);
    connect(reply, &QModbusReply::finished, [this, reply, reg, val] {

        if (reply->error() == QModbusDevice::NoError) {
            QVariant value = parseValue(reply->result().value(0), val.dataFormat);
            iDebug() << reg << value;
        } else if (reply->error() == QModbusDevice::ProtocolError) {
            iWarning() << "Modbus error" << reply->error();
        } else {
            iWarning() << "Modbus error" << reply->error();
        }
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
    default:
        return rawValue;
    }
}


