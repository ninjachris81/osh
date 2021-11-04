#include "systemtimemanager.h"
#include "time/systemtimemessage.h"

#include <QDebug>
#include <QDateTime>
#include "shared/time.h"

#include "macros.h"

QString SystemtimeManager::MANAGER_NAME = QStringLiteral("SystemtimeManager");

SystemtimeManager::SystemtimeManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_bcTimer, &QTimer::timeout, this, &SystemtimeManager::sendSystemtime);
}

void SystemtimeManager::init(LocalConfig* config) {
    qDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);

    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_NAME);
    Q_ASSERT(m_commManager != nullptr);

    m_bcTimer.setInterval(config->getInt("time.bcInterval", DEFAULT_SYSTIME_BC_INTERVAL));
    m_bcTimer.start();
}

QString SystemtimeManager::getName() {
    return MANAGER_NAME;
}

void SystemtimeManager::sendSystemtime() {
    qDebug() << Q_FUNC_INFO;

    if (m_commManager->isConnected()) {
        SystemtimeMessage systimeMessage(QDateTime::currentSecsSinceEpoch());
        m_commManager->sendMessage(systimeMessage);
    }
}

MessageBase::MESSAGE_TYPE SystemtimeManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

void SystemtimeManager::handleReceivedMessage(MessageBase* msg) {

}
