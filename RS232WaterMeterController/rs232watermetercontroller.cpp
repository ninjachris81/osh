#include "rs232watermetercontroller.h"

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

RS232WaterMeterController::RS232WaterMeterController(ControllerManager *manager, QString id, QObject *parent) : ControllerBase(manager, id, parent) {
    //connect(&m_statusTimer, &QTimer::timeout, this, &RS232WaterMeterController::retrieveStatus);
}

void RS232WaterMeterController::init() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    //m_statusTimer.setInterval(m_config->getInt(this, "status.interval", 20000));

    m_sensorCount = m_config->getInt(this, "sensorcount", 4);
    m_dataOffset = m_config->getInt(this, "sensoroffset", 9);
    m_stepAmountML = m_config->getInt(this, "stepMl", 250);

    m_serialClient = new SerialPortClient(m_config->getString(this, "serial.port", "COM1"), QSerialPort::Baud115200);
    m_serialClient->setLineMode(true);

    Helpers::safeConnect(m_serialClient, &SerialPortClient::connected, this, &RS232WaterMeterController::onSerialConnected, SIGNAL(connected()), SLOT(onSerialConnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::disconnected, this, &RS232WaterMeterController::onSerialDisconnected, SIGNAL(disconnected()), SLOT(onSerialDisconnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::lineReceived, this, &RS232WaterMeterController::onSerialDataReceived, SIGNAL(lineReceived(QByteArray)), SLOT(onSerialDataReceived(QByteArray)));
}

void RS232WaterMeterController::start() {
    iDebug() << Q_FUNC_INFO;

    m_serialClient->start();
}

void RS232WaterMeterController::handleMessage(ControllerMessage *msg) {
    iDebug() << Q_FUNC_INFO << msg->cmdType();
}


void RS232WaterMeterController::onSerialConnected() {
    iDebug() << Q_FUNC_INFO;

    //m_statusTimer.start();
    Q_EMIT(controllerConnected());
}

void RS232WaterMeterController::onSerialDisconnected() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Serial connection disconnected");
    //m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void RS232WaterMeterController::onSerialDataReceived(QByteArray data) {
    iDebug() << Q_FUNC_INFO << data;

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);

    if (err.error == QJsonParseError::NoError) {
        if (!doc.object().isEmpty()) {

            switch(doc.object().value("e").toInt()) {
            case EVENT_HEARTBEAT:
                // TODO
                break;
            case EVENT_DATA:
                increaseWaterLevel(doc.object().value("id").toInt());
                break;
            case EVENT_ERROR:
                m_warnManager->raiseWarning("Water sensor error " + QString::number(doc.object().value("id").toInt()));
                break;
            default:
                break;
            }


        } else {
            iWarning() << "Empty object";
        }
    } else {
        iWarning() << err.errorString();
    }
}

void RS232WaterMeterController::bindValueManager(ClientValueManager* valueManager, DatamodelBase* datamodel) {
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

void RS232WaterMeterController::onStateChanged() {
    iDebug() << Q_FUNC_INFO;
}

void RS232WaterMeterController::onErrorOccurred() {
    iDebug() << Q_FUNC_INFO;

    m_warnManager->raiseWarning("Relay connection disconnected");
    //m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}



void RS232WaterMeterController::retrieveStatus() {
    iDebug() << Q_FUNC_INFO;

}

DoubleValue* RS232WaterMeterController::getValue(uint8_t id) {
    if (id < m_sensorCount + m_dataOffset) {
        DoubleValue* val = m_valueMappings.at(id - m_dataOffset);
        Q_ASSERT(val != nullptr);
        return val;
    } else {
        iWarning() << "Invalid id" << id;
    }

    return nullptr;
}

void RS232WaterMeterController::increaseWaterLevel(uint8_t id) {
    iDebug() << Q_FUNC_INFO << id;

    DoubleValue* val = getValue(id);

    if (val != nullptr) {
        val->updateValue(val->rawValue().toDouble() + (m_stepAmountML / 1000), true);
        m_valueManager->publishValue(val);
    }
}
