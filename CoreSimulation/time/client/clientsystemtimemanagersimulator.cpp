#include "clientsystemtimemanagersimulator.h"

#include <QDebug>
#include "communication/communicationmanagerbase.h"
#include "time/systemtimemessage.h"

QLatin1String ClientSystemtimeManagerSimulator::MANAGER_ID = QLatin1String("ClientSystemtimeManagerSimulator");

ClientSystemtimeManagerSimulator::ClientSystemtimeManagerSimulator(QObject *parent) : ClientSystemtimeManager(parent)
{

}

void ClientSystemtimeManagerSimulator::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;
}

QString ClientSystemtimeManagerSimulator::id() {
    return MANAGER_ID;
}

void ClientSystemtimeManagerSimulator::enableSetTime(bool enable) {
    m_enableSetTime = enable;
}

void ClientSystemtimeManagerSimulator::setSystemTime(qint64 ts) {
    iDebug() << Q_FUNC_INFO;
    // TODO
    if (m_enableSetTime) {

    }
}

MessageBase::MESSAGE_TYPE ClientSystemtimeManagerSimulator::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SYSTEM_TIME;
}

void ClientSystemtimeManagerSimulator::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    SystemtimeMessage* systimeMessage = static_cast<SystemtimeMessage*>(msg);

    setSystemTime(systimeMessage->ts());
}
