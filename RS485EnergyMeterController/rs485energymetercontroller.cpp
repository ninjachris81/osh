#include "rs485energymetercontroller.h"

#include <QDebug>
#include <QSerialPort>
#include <QMutexLocker>

#include "helpers.h"

#include "controller/controllermanager.h"
#include "qthread.h"

RS485EnergyMeterController::RS485EnergyMeterController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent)
{
    connect(&m_statusTimer, &QTimer::timeout, this, &RS485EnergyMeterController::retrieveStatus);

}

void RS485EnergyMeterController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 10000));

    m_slaveId = m_config->getInt(this, "slaveId", 1);

    m_modbusClient.setConnectionParameter(QModbusDevice::SerialPortNameParameter, m_config->getString(this, "serial.port", "COM1"));
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialParityParameter, QSerialPort::EvenParity);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialBaudRateParameter, QSerialPort::Baud9600);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialDataBitsParameter, QSerialPort::Data8);
    m_modbusClient.setConnectionParameter(QModbusDevice::SerialStopBitsParameter, QSerialPort::OneStop);
    m_modbusClient.setTimeout(1000);
    m_modbusClient.setNumberOfRetries(1);

    registerInput(OrnoWe514::OrnoWe514_Input_Registers::COMM_ADDRESS, QVariant::Int, 1);
    //registerInput(OrnoWe514::OrnoWe514_Input_Registers::COMM_BAUD_RATE, QVariant::Int, 1);
    //registerInput(OrnoWe514::OrnoWe514_Input_Registers::FREQUENCY, QVariant::Int, 0.01);
    //registerInput(OrnoWe514::OrnoWe514_Input_Registers::PHASE_VOLTAGE_V1, QVariant::Int, 0.01);
    //registerInput(OrnoWe514_Input_Registers::PHASE_VOLTAGE_V2, QVariant::Int, 0.01);
    //registerInput(OrnoWe514_Input_Registers::PHASE_VOLTAGE_V3, QVariant::Int, 0.01);
    //registerInput(OrnoWe514::OrnoWe514_Input_Registers::PHASE_CURRENT_I1, QVariant::Double, 0.001);
    //registerInput(OrnoWe514_Input_Registers::PHASE_CURRENT_I2, QVariant::Double, 0.001);
    //registerInput(OrnoWe514_Input_Registers::PHASE_CURRENT_I3, QVariant::Double, 0.001);

    connect(&m_modbusClient, &QModbusDevice::stateChanged, this, &RS485EnergyMeterController::onStateChanged);
    connect(&m_modbusClient, &QModbusDevice::errorOccurred, this, &RS485EnergyMeterController::onErrorOccurred);
}

void RS485EnergyMeterController::registerInput(OrnoWe514::OrnoWe514_Input_Registers reg, QVariant::Type type, double multiplier) {
    RetrieveValue ret;

    ret.mqttName = Helpers::generateMqttNameFromConstant(QVariant::fromValue(reg).toString());
    ret.multiplier = multiplier;
    ret.type = type;

    m_inputRegisters.insert(reg, ret);
}

void RS485EnergyMeterController::bindValueManager(ValueManagerBase* valueManager, DatamodelBase* datamodel) {
    iInfo() << Q_FUNC_INFO;

    m_valueManager = valueManager;

    iInfo() << "Getting value group" << this->id();
    m_valueGroup = datamodel->valueGroup(this->id());
    Q_ASSERT(m_valueGroup != nullptr);

    for (OrnoWe514::OrnoWe514_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue ret = m_inputRegisters.value(reg);

        ValueBase* val = m_valueManager->getValue(m_valueGroup, ret.mqttName);
        if (val == nullptr) {
            iWarning() << "Value not in datamodel" << ret.mqttName;
            Q_ASSERT(val != nullptr);
        }

        m_inputMappings.insert(reg, val);
    }
}

void RS485EnergyMeterController::start() {
    iDebug() << Q_FUNC_INFO;

    iInfo() << "Connecting on" << m_modbusClient.connectionParameter(QModbusDevice::SerialPortNameParameter).toString();

    m_modbusClient.connectDevice();
}

void RS485EnergyMeterController::handleMessage(ControllerMessage *msg) {

}

void RS485EnergyMeterController::onStateChanged() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.state();

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

void RS485EnergyMeterController::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO << m_modbusClient.errorString();

    m_warnManager->raiseWarning("RS485 connection disconnected");
    m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void RS485EnergyMeterController::onDataReceived() {
    iDebug() << Q_FUNC_INFO;

    auto reply = qobject_cast<QModbusReply *>(sender());
    if (!reply)
        return;

    if (reply->error() == QModbusDevice::NoError) {
        QModbusResponse response = reply->rawResult();

        iDebug() << response.dataSize();
    } else if (reply->error() == QModbusDevice::ProtocolError) {
        iWarning() << "Modbus error" << reply->error();
    } else {
        iWarning() << "Modbus error" << reply->error();
    }

    reply->deleteLater();
}

void RS485EnergyMeterController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

    for (OrnoWe514::OrnoWe514_Input_Registers reg : m_inputRegisters.keys()) {
        RetrieveValue val = m_inputRegisters.value(reg);

        _readInput(reg, val);

        QThread::msleep(100);
        QThread::yieldCurrentThread();
    }
}

void RS485EnergyMeterController::_readInput(OrnoWe514::OrnoWe514_Input_Registers reg, RetrieveValue val) {
    QModbusDataUnit dataUnit(QModbusDataUnit::InputRegisters, reg, 1);

    QModbusReply* reply = m_modbusClient.sendReadRequest(dataUnit, m_slaveId);
    connect(reply, &QModbusReply::finished, [this, reply, reg, val] {

        if (reply->error() == QModbusDevice::NoError) {
            QVariant value = parseValue(reply->result().value(0), val.type, val.multiplier);
            iDebug() << reg << value;
            ValueBase *v = m_inputMappings.value(reg);
            m_valueManager->updateAndPublishValue(v, value);
        } else if (reply->error() == QModbusDevice::ProtocolError) {
            iWarning() << "Modbus error" << reply->error();
        } else {
            iWarning() << "Modbus error" << reply->error();
        }
    });
}

QVariant RS485EnergyMeterController::parseValue(quint16 value, QVariant::Type targetType, double multiplier) {
    double tempValue = value;
    tempValue *= multiplier;

    QVariant returnVal = QVariant::fromValue(tempValue);
    returnVal.convert(targetType);

    return returnVal;
}
