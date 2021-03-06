#include "communicationmanagerbase.h"

#include <QDateTime>
#include <QRandomGenerator64>
#include <QDebug>

#include "macros.h"
#include "controller/controllermanager.h"

QLatin1String CommunicationManagerBase::MANAGER_ID = QLatin1String("CommunicationManager");

CommunicationManagerBase::CommunicationManagerBase(QObject *parent) : ManagerBase(parent)
{
    connect(this, &CommunicationManagerBase::connected, [this] () {
        this->setIsConnected(true);
    });
    connect(this, &CommunicationManagerBase::disconnected, [this] () {
        this->setIsConnected(false);
    });
}

void CommunicationManagerBase::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ControllerManager);

    _init(config);
}

void CommunicationManagerBase::postInit() {
    iDebug() << Q_FUNC_INFO;

    QStringListIterator it(managerRegistration()->managerNames());
    while(it.hasNext())  {
        ManagerBase* manager = managerRegistration()->getManager(it.next());
        MessageBase::MESSAGE_TYPE messageType = manager->getMessageType();
        if (messageType != MessageBase::MESSAGE_TYPE_UNKNOWN) {
            iDebug() << "Register message type" << messageType << "for manager" << manager->id();
            m_managerMessageTypes.insert(messageType, manager);
        }
    }

    _startConnect();
}

QString CommunicationManagerBase::id() {
    return MANAGER_ID;
}

LogCat::LOGCAT CommunicationManagerBase::logCat() {
    return LogCat::COMMUNICATION;
}

quint64 CommunicationManagerBase::sendMessage(MessageBase &message) {
    if (_sendMessage(message)) {
        return static_cast<quint64>(QDateTime::currentMSecsSinceEpoch());
    } else {
        return SEND_ERROR;
    }
}

void CommunicationManagerBase::setIsConnected(bool connected) {
    if (m_isConnected != connected) {
        this->m_isConnected = connected;
        Q_EMIT(this->isConnectedChanged());
    }
}


bool CommunicationManagerBase::isConnected() {
    return m_isConnected;
}

MessageBase::MESSAGE_TYPE CommunicationManagerBase::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void CommunicationManagerBase::handleReceivedMessage(MessageBase* msg) {
    if (m_managerMessageTypes.contains(msg->getMessageType())) {
        m_managerMessageTypes.value(msg->getMessageType())->handleReceivedMessage(msg);
    } else {
        iWarning() << "No handlers for msg type" << msg->getMessageType();
    }
}
