#include "basicscripts.h"
#include <QDateTime>

#include "helpers.h"

BasicScripts::BasicScripts(DatamodelBase *datamodel, LocalStorage *localStorage, TaskStorage *taskStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("BasicScripts", datamodel, localStorage, taskStorage, valueManager, actorManager, parent)
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

bool BasicScripts::initTriggerCmdOnValue(QString valueSourceIds, QVariant triggerValue, QString actorId, int actorCmd, int retriggerTimeout) {
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
        m_localStorage->set("initTriggerCmdOnValue", "retriggerTimeout", valueSource->fullId(), retriggerTimeout);

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
    int retriggerTimeout = m_localStorage->get("initTriggerCmdOnValue", "retriggerTimeout", valueSource->fullId()).toInt();
    qint64 lastTrigger = m_localStorage->get("initTriggerCmdOnValue", "lastTrigger", valueSource->fullId(), 0).toULongLong();

    if (triggerValue.convert(valueSource->rawValue().type())) {
        if (triggerValue == valueSource->rawValue()) {
            if (lastTrigger == 0 || QDateTime::currentMSecsSinceEpoch() - lastTrigger > retriggerTimeout) {
                publishCmd(actor, static_cast<ACTOR_CMDS>(cmd), "initTriggerCmdOnValue_valueChanged");
                m_localStorage->set("initTriggerCmdOnValue", "lastTrigger", valueSource->fullId(), QDateTime:: currentMSecsSinceEpoch());
            } else {
                qInfo() << "Trigger too recent" << lastTrigger << retriggerTimeout;
            }
        }
    } else {
        qWarning() << "Cannot convert to target type" << triggerValue << valueSource->rawValue();
    }
}

bool BasicScripts::initFollowActor(QString actorSourceId, QString triggerActorId, int followMode) {
    iInfo() << Q_FUNC_INFO;

    ActorBase *sourceActor = m_datamodel->actor(actorSourceId);
    Q_ASSERT(sourceActor != nullptr);

    ActorBase *triggerActor = m_datamodel->actor(triggerActorId);
    Q_ASSERT(triggerActor != nullptr);

    m_localStorage->setObject("initFollowActor", "triggerActorId", sourceActor->fullId(), triggerActor);

    if (followMode & 1) {      // only cmd
        Helpers::safeConnect(sourceActor, &ActorBase::cmdTriggered, this, &BasicScripts::initFollowActor_cmdTriggered, SIGNAL(cmdTriggered(ACTOR_CMDS)), SLOT(initFollowActor_cmdTriggered(ACTOR_CMDS)));
        iDebug() << "Connecting cmd of actor" << actorSourceId << "to" << triggerActor;
    }
    if (followMode & 2) {       // only value
        Helpers::safeConnect(sourceActor, &ActorBase::valueChanged, this, &BasicScripts::initFollowActor_valueChanged, SIGNAL(valueChanged()), SLOT(initFollowActor_valueChanged()));
        iDebug() << "Connecting value of actor" << actorSourceId << "to" << triggerActor;
    }

    return true;
}

void BasicScripts::initFollowActor_cmdTriggered(ACTOR_CMDS cmd) {

    ActorBase* sourceActor = static_cast<ActorBase*>(sender());
    ActorBase *triggerActor = static_cast<AudioPlaybackActor*>(m_localStorage->getObject("initFollowActor", "triggerActorId", sourceActor->fullId()));

    publishCmd(triggerActor, static_cast<ACTOR_CMDS>(cmd), "initFollowActor");
}

void BasicScripts::initFollowActor_valueChanged() {

    ActorBase* sourceActor = static_cast<ActorBase*>(sender());
    ActorBase *triggerActor = static_cast<AudioPlaybackActor*>(m_localStorage->getObject("initFollowActor", "triggerActorId", sourceActor->fullId()));

    publishValue(triggerActor, sourceActor->rawValue());
}
