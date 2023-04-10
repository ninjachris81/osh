#include "scriptbase.h"

#include <QDateTime>

#include "helpers.h"


QLatin1String ScriptBase::INTERVAL_OFF_DURATIONS = QLatin1String("interval_off_durations_");
QLatin1String ScriptBase::INTERVAL_ON_DURATIONS = QLatin1String("interval_on_durations_");
QLatin1String ScriptBase::INTERVAL_LAST_CHANGES = QLatin1String("interval_lastChanges_");
QLatin1String ScriptBase::INTERVAL_STATES = QLatin1String("interval_states_");

QLatin1String ScriptBase::TIMOUT_LAST_TS = QLatin1String("last_ts_");

ScriptBase::ScriptBase(QString name, DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent) : Identifyable(name), QObject(parent)
  , m_datamodel(datamodel), m_localStorage(localStorage), m_valueManager(valueManager), m_actorManager(actorManager)
{

}

LogCat::LOGCAT ScriptBase::logCat() {
    return LogCat::PROCESSOR;
}


/*
void ScriptBase::publishValue(QString fullId, QVariant value) {
    ValueBase* val = m_datamodel->values().value(fullId);
    publishValue(val, value);
}
*/

void ScriptBase::publishCmd(QString fullId, int cmd, QString reason) {
    ActorBase* actor = m_datamodel->actor(fullId);
    publishCmd(actor, static_cast<actor::ACTOR_CMDS>(cmd), reason);
}

void ScriptBase::publishCmd(QString fullId, int cmd, QVariant value, QString reason) {
    ActorBase* actor = m_datamodel->actor(fullId);
    publishCmd(actor, static_cast<actor::ACTOR_CMDS>(cmd), value, reason);
}

void ScriptBase::publishValue(ValueBase* val, QVariant value) {
    m_valueManager->updateAndPublishValue(val, value);
}

void ScriptBase::publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QString reason) {
    iDebug() << actor->fullId() << cmd << reason;
    actor->triggerCmd(cmd, reason);
    m_actorManager->publishCmd(actor, cmd);
    m_valueManager->publishValue(actor);
}

void ScriptBase::publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QVariant value, QString reason) {
    iDebug() << actor->fullId() << cmd << value << reason;
    actor->updateValue(value, true);
    actor->triggerCmd(cmd, reason);
    m_actorManager->publishCmd(actor, cmd, value);
    m_valueManager->publishValue(actor);
}

void ScriptBase::setTimeout(QString key) {
    m_localStorage->set("setTimeout", TIMOUT_LAST_TS, key, QDateTime::currentMSecsSinceEpoch());
}

bool ScriptBase::isTimeout(QString key, quint64 timeoutMs, bool clearTimeoutIfTrue) {
    quint64 lastOn = m_localStorage->get("setTimeout", TIMOUT_LAST_TS, key, 0).toULongLong();
    bool isTo = (lastOn > 0 && QDateTime::currentMSecsSinceEpoch() - lastOn > timeoutMs);

    if (isTo && clearTimeoutIfTrue) {
        clearTimeout(key);
    }

    return isTo;
}

quint64 ScriptBase::getTimeout(QString key) {
    return m_localStorage->get("setTimeout", TIMOUT_LAST_TS, key, 0).toULongLong();
}

void ScriptBase::clearTimeout(QString key) {
    m_localStorage->unset("setTimeout", TIMOUT_LAST_TS, key);
}

void ScriptBase::setupInterval(QString key, qulonglong durationOffMs, qulonglong durationOnMs, bool resetState) {
    if (durationOffMs > 0 && durationOnMs > 0) {
        iDebug() << "Setup interval" << key << durationOffMs << durationOnMs << resetState;

        m_localStorage->set("setupInterval", INTERVAL_OFF_DURATIONS, key, durationOffMs);
        m_localStorage->set("setupInterval", INTERVAL_ON_DURATIONS, key, durationOnMs);
        if (resetState) {
            m_localStorage->set("setupInterval", INTERVAL_LAST_CHANGES, key, 0);
            m_localStorage->set("setupInterval", INTERVAL_STATES, key, false);
        }
    } else {
        iWarning() << "Invalid parameters" << durationOffMs << durationOnMs;
    }
}

bool ScriptBase::getIntervalState(QString key) {
    qulonglong durationOffMs = m_localStorage->get("setupInterval", INTERVAL_OFF_DURATIONS, key, 0).toULongLong();
    qulonglong durationOnMs = m_localStorage->get("setupInterval", INTERVAL_ON_DURATIONS, key, 0).toULongLong();
    qulonglong lastChangeMs = m_localStorage->get("setupInterval", INTERVAL_LAST_CHANGES, key, 0).toULongLong();
    bool state = m_localStorage->get("setupInterval", INTERVAL_STATES, key, false).toBool();

    if (state) {
        // check if we have to switch off
        if (QDateTime::currentMSecsSinceEpoch() - lastChangeMs >= durationOnMs) {
            // ok, switch off
            m_localStorage->set("setupInterval", INTERVAL_STATES, key, false);
            state = false;
            m_localStorage->set("setupInterval", INTERVAL_LAST_CHANGES, key, QDateTime::currentMSecsSinceEpoch());
            iDebug() << "Interval switching to" << key << state;
        }
    } else {
        // check if we have to switch on
        if (QDateTime::currentMSecsSinceEpoch() - lastChangeMs >= durationOffMs) {
            // ok, switch on
            m_localStorage->set("setupInterval", INTERVAL_STATES, key, true);
            state = true;
            m_localStorage->set("setupInterval", INTERVAL_LAST_CHANGES, key, QDateTime::currentMSecsSinceEpoch());
            iDebug() << "Interval switching to" << key << state;
        }
    }

    return state;
}

void ScriptBase::clearInterval(QString key) {
    m_localStorage->unset("setupInterval", INTERVAL_OFF_DURATIONS, key);
    m_localStorage->unset("setupInterval", INTERVAL_ON_DURATIONS, key);
    m_localStorage->unset("setupInterval", INTERVAL_LAST_CHANGES, key);
    m_localStorage->unset("setupInterval", INTERVAL_STATES, key);
}


bool ScriptBase::isWithin(quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo) {
    int from = ((hourFrom * 60) + minuteFrom) * 60 * 1000;
    int to = ((hourTo * 60) + minuteTo) * 60 * 1000;

    if (from == to) return 0;

    qint64 now = QTime::currentTime().msecsSinceStartOfDay();
    if (from < to) {
        // normal case
        return now > from && now < to;
    } else {
        // day limit
        return now > from || now < to;
    }
}
