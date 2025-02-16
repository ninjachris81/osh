#include "basicscripts.h"
#include <QDateTime>

#include "helpers.h"

BasicScripts::BasicScripts(DatamodelBase *datamodel, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("BasicScripts", datamodel, localStorage, valueManager, actorManager, parent)
{

}

bool BasicScripts::initConnectValues(QString valueSourceIds, QString valueTargetId) {
    iInfo() << Q_FUNC_INFO;

    ValueBase *valueTarget = m_datamodel->value(valueTargetId);
    if (valueTarget == nullptr) {
        // could be actor or value
        valueTarget = m_datamodel->actor(valueTargetId);
    }

    Q_ASSERT(valueTarget != nullptr);

    for (QString valueSourceId : valueSourceIds.split("|", QString::SkipEmptyParts)) {
        ValueBase *valueSource = m_datamodel->value(valueSourceId);
        if (valueSource == nullptr) {
            // could be actor or value
            valueSource = m_datamodel->actor(valueSourceId);
        }
        Q_ASSERT(valueSource != nullptr);

        m_localStorage->setObject("initConnectValues", "valueTarget", valueSource->fullId(), valueTarget);
        Helpers::safeConnect(valueSource, &ValueBase::valueChanged, this, &BasicScripts::initConnectValues_valueChanged, SIGNAL(valueChanged()), SLOT(initConnectValues_valueChanged()));
    }

    return true;
}

void BasicScripts::initConnectValues_valueChanged() {
    iInfo() << Q_FUNC_INFO;

    ValueBase* valueSource = static_cast<ValueBase*>(sender());
    ValueBase *valueTarget = static_cast<ValueBase*>(m_localStorage->getObject("initConnectValues", "valueTarget", valueSource->fullId()));

    publishValue(valueTarget, valueSource->rawValue());
}

bool BasicScripts::initTriggerCmdOnValue(QString valueSourceIds, QVariant triggerValue, QString actorId, int actorCmd) {
    iInfo() << Q_FUNC_INFO;

    ActorBase *actor = m_datamodel->actor(actorId);
    Q_ASSERT(actor != nullptr);


    for (QString valueSourceId : valueSourceIds.split("|", QString::SkipEmptyParts)) {
        ValueBase *valueSource = m_datamodel->value(valueSourceId);
        if (valueSource == nullptr) {
            // could be actor or value
            valueSource = m_datamodel->actor(valueSourceId);
        }
        Q_ASSERT(valueSource != nullptr);

        m_localStorage->setObject("initTriggerCmdOnValue", "actor", valueSource->fullId(), actor);
        m_localStorage->set("initTriggerCmdOnValue", "actorCmd", valueSource->fullId(), actorCmd);
        m_localStorage->set("initTriggerCmdOnValue", "triggerValue", valueSource->fullId(), triggerValue);

        Helpers::safeConnect(valueSource, &ValueBase::valueChanged, this, &BasicScripts::initTriggerCmdOnValue_valueChanged, SIGNAL(valueChanged()), SLOT(initTriggerCmdOnValue_valueChanged()));
    }

    return true;
}

void BasicScripts::initTriggerCmdOnValue_valueChanged() {
    iDebug() << Q_FUNC_INFO;

    ValueBase* valueSource = static_cast<ValueBase*>(sender());
    ActorBase *actor = static_cast<ActorBase*>(m_localStorage->getObject("initTriggerCmdOnValue", "actor", valueSource->fullId()));
    int cmd = m_localStorage->get("initTriggerCmdOnValue", "actorCmd", valueSource->fullId()).toInt();
    QVariant triggerValue = m_localStorage->get("initTriggerCmdOnValue", "triggerValue", valueSource->fullId());

    if (triggerValue.convert(valueSource->rawValue().type())) {
        if (triggerValue == valueSource->rawValue()) {
            publishCmd(actor, static_cast<actor::ACTOR_CMDS>(cmd), "initTriggerCmdOnValue_valueChanged");
        }
    } else {
        qWarning() << "Cannot convert to target type" << triggerValue << valueSource->rawValue();
    }
}

bool BasicScripts::initFollowActor(QString actorSourceId, QString triggerActorId) {
    iInfo() << Q_FUNC_INFO;

    ActorBase *sourceActor = m_datamodel->actor(actorSourceId);
    Q_ASSERT(sourceActor != nullptr);

    ActorBase *triggerActor = m_datamodel->actor(triggerActorId);
    Q_ASSERT(triggerActor != nullptr);

    m_localStorage->setObject("initFollowActor", "triggerActorId", sourceActor->fullId(), triggerActor);

    Helpers::safeConnect(sourceActor, &ActorBase::cmdTriggered, this, &BasicScripts::initFollowActor_cmdTriggered, SIGNAL(cmdTriggered(actor::ACTOR_CMDS)), SLOT(initFollowActor_cmdTriggered(actor::ACTOR_CMDS)));
}

void BasicScripts::initFollowActor_cmdTriggered(actor::ACTOR_CMDS cmd) {

    ActorBase* sourceActor = static_cast<ActorBase*>(sender());
    ActorBase *triggerActor = static_cast<AudioPlaybackActor*>(m_localStorage->getObject("initFollowActor", "triggerActorId", sourceActor->fullId()));

    triggerActor->triggerCmd(cmd, "initFollowActor");
}
