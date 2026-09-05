#include "rs232inputcontroller.h"

#include "controller/controllermanager.h"
#include "helpers.h"

#include <QDateTime>

RS232InputController::RS232InputController(ControllerManager* manager, QString id, QObject *parent)
    : DigitalInputControllerBase (manager, id, parent)
{}

void RS232InputController::init() {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER_X(m_manager, ValueManagerBase);
    m_valueManager = m_manager->getManager<ValueManagerBase>(ValueManagerBase::MANAGER_ID);

    REQUIRE_MANAGER_X(m_manager, ClientSystemWarningsManager);
    m_clientSystemWarningsManager = m_manager->getManager<ClientSystemWarningsManager>(ClientSystemWarningsManager::MANAGER_ID);

    if (m_config->getInt(this, "inputCount", 0) > 0) {
        m_inputCount = m_config->getInt(this, "inputCount", 0);
    }

    DigitalInputControllerBase::init();

    m_serialClient = new SerialPortClient(m_config->getString(this, "serial.port", "COM1"), QSerialPort::Baud9600);
    m_serialClient->setLineMode(true);

    Helpers::safeConnect(m_serialClient, &SerialPortClient::connected, this, &RS232InputController::onSerialConnected, SIGNAL(connected()), SLOT(onSerialConnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::disconnected, this, &RS232InputController::onSerialDisconnected, SIGNAL(disconnected()), SLOT(onSerialDisconnected()));
    Helpers::safeConnect(m_serialClient, &SerialPortClient::lineReceived, this, &RS232InputController::onSerialDataReceived, SIGNAL(lineReceived(QByteArray)), SLOT(onSerialDataReceived(QByteArray)));
}

void RS232InputController::start() {
    iDebug() << Q_FUNC_INFO;

    m_serialClient->start();
}

quint8 RS232InputController::inputCount() {
    return m_inputCount;
}


void RS232InputController::onSerialConnected() {
    iDebug() << Q_FUNC_INFO;

    //m_statusTimer.start();
    Q_EMIT(controllerConnected());
}

void RS232InputController::onSerialDisconnected() {
    iDebug() << Q_FUNC_INFO;

    m_clientSystemWarningsManager->raiseWarning("Serial connection disconnected", QtCriticalMsg);
    //m_statusTimer.stop();
    Q_EMIT(controllerDisconnected());
}

void RS232InputController::onSerialDataReceived(QByteArray data) {
    iDebug() << Q_FUNC_INFO << data;

    if (data.at(data.length()-2) == '\r' && data.at(data.length()-1) == '\n') {
        data.chop(2);
    }

    QString msg(data);
    QStringList tokens = msg.split(',');
    if (tokens.length() == 2) {
        int index = tokens.at(0).toInt();
        bool state= tokens.at(1).toInt() == 1;
        if (index < inputCount()) {
            m_valueManager->updateAndPublishValue(m_valueMappings.at(index), state);
        } else {
            iDebug() << "Index out of range" << index;
        }
    } else {
        iWarning() << "Invalid msg" << msg;
    }

}
