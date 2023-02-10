#include "actorconfigmanager.h"

#include <QDebug>

#include "actor/actorconfigmessage.h"
#include "value/client/clientvaluemanager.h"
#include "macros.h"

QLatin1String ActorConfigManager::MANAGER_ID = QLatin1String("ActorConfigManager");

ActorConfigManager::ActorConfigManager(QObject *parent) : ManagerBase(parent)
{

}

LogCat::LOGCAT ActorConfigManager::logCat() {
    return LogCat::ACTOR;
}

void ActorConfigManager::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(ActorManager);
    m_actorManager = getManager<ActorManager>(ActorManager::MANAGER_ID);

    REQUIRE_MANAGER(CommunicationManagerBase);
    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    if (managerRegistration()->instanceRole() == ManagerRegistration::SERVER) {
        connect(m_commManager, &CommunicationManagerBase::connected, this, &ActorConfigManager::onBroadcastConfig);
    }
}

void ActorConfigManager::onBroadcastConfig() {
    iInfo() << Q_FUNC_INFO;

    for (ActorBase* actor : m_actorManager->actors()) {
        if (!actor->configKeys().isEmpty()) {
            QVariantMap configMap;

            for (QString configKey : actor->configKeys()) {
                QVariant configValue = actor->getConfig(configKey, QVariant());
                if (configValue.isValid()) {
                    configMap.insert(configKey, configValue);
                }
            }

            if (!configMap.isEmpty()) {
                iDebug() << actor->fullId() << configMap;
                ActorConfigMessage configMessage(actor->valueGroup()->id(), actor->id(), configMap);
                m_commManager->sendMessage(configMessage);
            }
        }
    }
}

QString ActorConfigManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE ActorConfigManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_ACTOR_CONFIG;
}

void ActorConfigManager::handleReceivedMessage(MessageBase* msg) {
    ActorConfigMessage* actorConfigMessage = static_cast<ActorConfigMessage*>(msg);
    iDebug() << Q_FUNC_INFO << actorConfigMessage->fullId();

    ActorBase* actor = m_actorManager->getActor(actorConfigMessage->fullId());
    if (actor != nullptr) {
        actor->setConfig(actorConfigMessage->values());
    } else {
        iWarning() << "Invalid actor" << actorConfigMessage->fullId();
    }
}
