#include "commonscripts.h"
#include "actor/toggleactor.h"

#include <QDateTime>

#include "helpers.h"
#include "qsignalmapper.h"

QLatin1String CommonScripts::INTERVAL_OFF_DURATIONS = QLatin1String("interval_off_durations_");
QLatin1String CommonScripts::INTERVAL_ON_DURATIONS = QLatin1String("interval_on_durations_");
QLatin1String CommonScripts::INTERVAL_LAST_CHANGES = QLatin1String("interval_lastChanges_");
QLatin1String CommonScripts::INTERVAL_STATES = QLatin1String("interval_states_");


CommonScripts::CommonScripts(DatamodelBase *datamodel, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("CommonScripts", parent), m_datamodel(datamodel), m_localStorage(localStorage), m_valueManager(valueManager), m_actorManager(actorManager)
{
}

/*
 * Returns true if the function has been called
*/
/*
bool CommonScripts::ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant invalidValue, QJSValue function) {
    iDebug() << Q_FUNC_INFO << actualValue << expectedValue;

    QVariant actual = actualValue->isValid() ? actualValue->rawValue() : invalidValue;
    QVariant expected = expectedValue->isValid() ?  expectedValue->rawValue() : invalidValue;

    if (actual != expected) {
        // call func
        if (function.isCallable()) {
            iDebug() << "Call function" << actual << expected;
            QJSValueList paramList;
            paramList << m_engine->toScriptValue(expected);
            function.call(paramList);
            return true;
        } else {
            iWarning() << "Parameter is not a function" << function.toString();
        }
    } else {
        iDebug() << "Same value" << actual << expected;
    }

    return false;
}
*/

bool CommonScripts::applySwitchMotionLogic(QString lightActorFullId, QString inputSensorFullId, QString motionSensorFullId, QString brightnessSensorFullId, int brightnessThreshold, quint64 triggerTimeoutMs, quint64 motionSensorGracePeriodMs) {
    if (m_datamodel->actors().contains(lightActorFullId) && m_datamodel->values().contains(inputSensorFullId) && m_datamodel->values().contains(motionSensorFullId) && m_datamodel->values().contains(brightnessSensorFullId)) {
        ActorBase* lightActor = m_datamodel->actors().value(lightActorFullId);
        ValueBase* inputSensor = m_datamodel->values().value(inputSensorFullId);
        ValueBase* motionSensor = m_datamodel->values().value(motionSensorFullId);
        ValueBase* brightnessSensor = m_datamodel->values().value(brightnessSensorFullId);

        QVariant actualValue = lightActor->rawValue();
        QVariant expectedValue;

        QString lastTsMotionSensorKey = "lastTs_" + motionSensorFullId;
        QString graceMotionSensorKey = "grace_" + motionSensorFullId;
        QString lastTsInputKey = "lastTs_" + inputSensorFullId;
        QString lastValueInputKey = "lastValue_" + inputSensorFullId;

        QString triggerReason;

        bool inputTriggered = false;

        if (inputSensor->isValid()) {
            QVariant lastValue = m_localStorage->get(lastValueInputKey);

            if (lastValue.isValid() && inputSensor->rawValue() != lastValue && inputSensor->rawValue().toBool()) {
                inputTriggered = true;
                iDebug() << "Input sensor triggered";
            }

            m_localStorage->set(lastValueInputKey, inputSensor->rawValue());
        }

        if (actualValue.isValid() && actualValue.toBool() && inputSensor->isValid() && inputTriggered) {
            // toggle to OFF
            iDebug() << "Toggle off with grace period for motion sensor";
            expectedValue = false;

            triggerReason = "Input trigger";
            m_localStorage->set(lastTsMotionSensorKey, 0);
            m_localStorage->set(lastTsInputKey, 0);
            m_localStorage->set(graceMotionSensorKey, QDateTime::currentMSecsSinceEpoch());
        } else {
            // update last values
            if (brightnessSensor->isValid() && brightnessSensor->rawValue().toInt() < brightnessThreshold) {
                if (motionSensor->isValid() && motionSensor->rawValue().toBool() && (QDateTime::currentMSecsSinceEpoch() - m_localStorage->get(graceMotionSensorKey, 0).toULongLong() > motionSensorGracePeriodMs)) {
                    m_localStorage->set(lastTsMotionSensorKey, QDateTime::currentMSecsSinceEpoch());
                    triggerReason = "Motion sensor";
                }
            }

            if (inputSensor->isValid() && inputTriggered) {
                m_localStorage->set(lastTsInputKey, QDateTime::currentMSecsSinceEpoch());
                triggerReason = "Input trigger";
            }

            quint64 lastContact = qMax(m_localStorage->get(lastTsMotionSensorKey, 0).toULongLong(), m_localStorage->get(lastTsInputKey, 0).toULongLong());

            iDebug() << "Last contact" << lastContact;

            if (lastContact > 0 && QDateTime::currentMSecsSinceEpoch() - lastContact < triggerTimeoutMs) {
                expectedValue = true;
            } else if (inputSensor->isValid() && motionSensor->isValid()) {
                triggerReason = "Timeout";
                expectedValue = false;
            }
        }

        // finally set the value
        if (actualValue != expectedValue && expectedValue.isValid()) {
            lightActor->triggerCmd(expectedValue.toBool() ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF, triggerReason);
        }

        return true;
    } else {
        iWarning() << "Invalid parameters" << lightActorFullId << inputSensorFullId << motionSensorFullId << brightnessSensorFullId;
        return false;
    }
}

bool CommonScripts::initSwitchLogic(QString lightActorFullId, QString inputSensorFullId, QString toggleActorFullId) {
    DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_datamodel->actors().value(lightActorFullId));
    BooleanValue* inputSensor = static_cast<BooleanValue*>(m_datamodel->values().value(inputSensorFullId));
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actors().value(toggleActorFullId));

    Q_ASSERT(lightRelayActor != nullptr);
    Q_ASSERT(inputSensor != nullptr);
    Q_ASSERT(toggleActor != nullptr);

    m_localStorage->setObject("switch_toggle_actor_" + inputSensorFullId, toggleActor);
    Helpers::safeConnect(inputSensor, &BooleanValue::valueChanged, this, &CommonScripts::onInitSwitchLogic_inputSensorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_inputSensorValueChanged()));

    m_localStorage->setObject("switch_light_relay_" + toggleActorFullId, lightRelayActor);
    Helpers::safeConnect(toggleActor, &ToggleActor::valueChanged, this, &CommonScripts::onInitSwitchLogic_toggleActorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_toggleActorValueChanged()));

    return true;
}

void CommonScripts::onInitSwitchLogic_inputSensorValueChanged() {
    BooleanValue* inputSensor = static_cast<BooleanValue*>(sender());
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_localStorage->getObject("switch_toggle_actor_" + inputSensor->fullId()));

    QString lastInputValKey = "lastVal_" + inputSensor->fullId();
    bool lastInputVal = m_localStorage->get(lastInputValKey, false).toBool();
    if (lastInputVal != inputSensor->rawValue().toBool()) {
        m_localStorage->set(lastInputValKey, inputSensor->rawValue().toBool());

        if (inputSensor->rawValue().isValid() && inputSensor->rawValue().toBool()) {
            publishCmd(toggleActor, actor::ACTOR_CMD_TOGGLE, "input sensor");
        }
    }
}

void CommonScripts::onInitSwitchLogic_toggleActorValueChanged() {
    ToggleActor* toggleActor = static_cast<ToggleActor*>(sender());

    DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_localStorage->getObject("switch_light_relay_" + toggleActor->fullId()));

    QString lastTsInputKey = "lastToggleTs_" + toggleActor->fullId();

    if (toggleActor->rawValue().toBool()) {
        m_localStorage->set(lastTsInputKey, QDateTime::currentMSecsSinceEpoch());
    } else {
        m_localStorage->unset(lastTsInputKey);
    }

    publishCmd(lightRelayActor, toggleActor->rawValue().toBool() ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF, "toggle");
}


bool CommonScripts::applySwitchTimeoutLogic(QString toggleActorFullId, quint64 triggerTimeoutMs) {
    QString lastTsInputKey = "lastToggleTs_" + toggleActorFullId;

    // check for timeout
    quint64 lastOn = m_localStorage->get(lastTsInputKey, 0).toULongLong();
    if (lastOn > 0 && QDateTime::currentMSecsSinceEpoch() - lastOn > triggerTimeoutMs) {
        ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actors().value(toggleActorFullId));

        if (toggleActor->rawValue().toBool()) {
            m_localStorage->unset(lastTsInputKey);
            publishCmd(toggleActor, actor::ACTOR_CMD_TOGGLE, "Timeout");
        } else {
            // hmm, already off
        }
    }

    return true;
}

bool CommonScripts::applyTempValveLogic(QString tempFullId, QString tempTargetFullId, QString tempValveActorFullId, int adjustIntervalMs, double fullDeltaThresholdTemp, int factorIntervalMs) {
    if (m_datamodel->actors().contains(tempValveActorFullId)) {
        QString valveKey = "temp_valve_" + tempValveActorFullId;
        QString lastAdjustKey = "temp_valve_last_adj_" + tempValveActorFullId;
        qlonglong lastAdjustMs = m_localStorage->get(lastAdjustKey, 0).toULongLong();
        ActorBase* tempValve = m_datamodel->actors().value(tempValveActorFullId);

        if (lastAdjustMs == 0 || QDateTime::currentMSecsSinceEpoch() - lastAdjustMs > adjustIntervalMs) {
            if (m_datamodel->values().contains(tempFullId) && m_datamodel->values().contains(tempTargetFullId)) {
                ValueBase* temp = m_datamodel->values().value(tempFullId);
                ValueBase* targetTemp = m_datamodel->values().value(tempTargetFullId);

                if (temp->isValid() && targetTemp->isValid()) {
                    double deltaTemp = targetTemp->rawValue().toDouble() - temp->rawValue().toDouble();

                    // positive delta: open valve
                    if (deltaTemp > 0) {
                        if (deltaTemp > fullDeltaThresholdTemp) {
                            // always on, delta is too big
                            if (!tempValve->rawValue().toBool()) {
                                tempValve->triggerCmd(actor::ACTOR_CMD_ON, "Always on");
                            }
                        } else {
                            qlonglong offMs;
                            qlonglong onMs;

                            offMs = fullDeltaThresholdTemp - deltaTemp;
                            onMs = fullDeltaThresholdTemp - offMs;

                            setupInterval(valveKey, offMs * factorIntervalMs, onMs * factorIntervalMs, false);
                        }
                    } else {
                        clearInterval(valveKey);
                    }

                    m_localStorage->set(lastAdjustKey, QDateTime::currentMSecsSinceEpoch());
                    return true;
                } else {
                    clearInterval(valveKey);
                    return false;
                }
            } else {
                iWarning() << "Invalid parameters" << tempFullId << tempTargetFullId;
                clearInterval(valveKey);
                return false;
            }

            // ok, adjust
            m_localStorage->set(lastAdjustKey, QDateTime::currentMSecsSinceEpoch());
        } else {
            // check interval
            bool targetValveState = getIntervalState(valveKey);

            if (tempValve->rawValue().toBool() != targetValveState) {
                tempValve->triggerCmd(targetValveState ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF, "Interval timeout");
            }

            return true;
        }
    } else {
        iWarning() << "Invalid parameters" << tempValveActorFullId;
        return false;
    }
}

bool CommonScripts::applyMotionLogic(QString radarFullId, QString pirFullId, QString motionFullId) {
    ValueBase* radarVal = m_datamodel->values().value(radarFullId);
    ValueBase* pirVal = m_datamodel->values().value(pirFullId);
    ValueBase* motionVal = m_datamodel->values().value(motionFullId);

    if (radarVal->isValid() && radarVal->rawValue().toBool()) {
        if (motionVal->updateValue(true)) {
            //publishValue(motionVal, true);
        }
    } else if (pirVal->isValid() && pirVal->rawValue().toBool()) {
        if (motionVal->updateValue(true)) {
            //publishValue(motionVal, true);
        }
    } else {
        if (motionVal->updateValue(false)) {
            //publishValue(motionVal, false);
        }
    }
    return true;
}

bool CommonScripts::applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString motionFullId, quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo) {
    ShutterActor* shutterActor = static_cast<ShutterActor*>(m_datamodel->actors().value(shutterFullId));
    EnumValue* shutterMode = static_cast<EnumValue*>(m_datamodel->values().value(shutterModeFullId));

    Q_ASSERT(shutterActor != nullptr);
    Q_ASSERT(shutterMode != nullptr);

    bool motionActive = false;
    if (!motionFullId.isEmpty()) {
        ValueBase* motionVal = m_datamodel->values().value(motionFullId);
        motionActive = motionVal->rawValue().toBool();
    }

    bool isDownTime = isWithin(hourFrom, minuteFrom, hourTo, minuteTo);

    if (shutterActor->isValid() && shutterMode->rawValue().toInt() == SHUTTER_OPERATION_MODE_AUTO) {
        if (isDownTime) {
            // down: check is motion active
            if (!motionActive && shutterActor->rawValue().toInt() != SHUTTER_CLOSED) {
                publishCmd(shutterActor, actor::ACTOR_CMD_DOWN, "applyShutterLogic");
            } else {
                iDebug() << "Room still active - pausing shutter actions";
            }
        } else {
            // up: just time-based
            if (shutterActor->rawValue().toInt() != SHUTTER_OPENED) {
                publishCmd(shutterActor, actor::ACTOR_CMD_UP, "applyShutterLogic");
            }
        }
        return true;
    } else {
        iWarning() << "Invalid parameters" << shutterFullId << motionFullId;
        return false;
    }
}

/*
void CommonScripts::publishValue(QString fullId, QVariant value) {
    ValueBase* val = m_datamodel->values().value(fullId);
    publishValue(val, value);
}
*/

void CommonScripts::publishCmd(QString fullId, int cmd, QString reason) {
    ActorBase* actor = m_datamodel->actors().value(fullId);
    publishCmd(actor, static_cast<actor::ACTOR_CMDS>(cmd), reason);
}

void CommonScripts::publishCmd(QString fullId, int cmd, QVariant value, QString reason) {
    ActorBase* actor = m_datamodel->actors().value(fullId);
    publishCmd(actor, static_cast<actor::ACTOR_CMDS>(cmd), value, reason);
}

/*
void CommonScripts::publishValue(ValueBase* val, QVariant value) {
    val->updateValue(value);
    m_valueManager->publishValue(val);
}
*/

void CommonScripts::publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QString reason) {
    iDebug() << actor->fullId() << cmd << reason;
    //actor->triggerCmd(cmd, reason);
    m_actorManager->publishCmd(actor, cmd);
}

void CommonScripts::publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QVariant value, QString reason) {
    iDebug() << actor->fullId() << cmd << value << reason;
    //actor->triggerCmd(cmd, reason);
    m_actorManager->publishCmd(actor, cmd, value);
}

void CommonScripts::setupInterval(QString key, qulonglong durationOffMs, qulonglong durationOnMs, bool resetState) {
    if (durationOffMs > 0 && durationOnMs > 0) {
        iDebug() << "Setup interval" << key << durationOffMs << durationOnMs << resetState;

        m_localStorage->set(INTERVAL_OFF_DURATIONS + key, durationOffMs);
        m_localStorage->set(INTERVAL_ON_DURATIONS + key, durationOnMs);
        if (resetState) {
            m_localStorage->set(INTERVAL_LAST_CHANGES + key, 0);
            m_localStorage->set(INTERVAL_STATES + key, false);
        }
    } else {
        iWarning() << "Invalid parameters" << durationOffMs << durationOnMs;
    }
}

bool CommonScripts::getIntervalState(QString key) {
    qulonglong durationOffMs = m_localStorage->get(INTERVAL_OFF_DURATIONS + key, 0).toULongLong();
    qulonglong durationOnMs = m_localStorage->get(INTERVAL_ON_DURATIONS + key, 0).toULongLong();
    qulonglong lastChangeMs = m_localStorage->get(INTERVAL_LAST_CHANGES + key, 0).toULongLong();
    bool state = m_localStorage->get(INTERVAL_STATES + key, false).toBool();

    if (state) {
        // check if we have to switch off
        if (QDateTime::currentMSecsSinceEpoch() - lastChangeMs >= durationOnMs) {
            // ok, switch off
            m_localStorage->set(INTERVAL_STATES + key, false);
            state = false;
            m_localStorage->set(INTERVAL_LAST_CHANGES + key, QDateTime::currentMSecsSinceEpoch());
            iDebug() << "Interval switching to" << key << state;
        }
    } else {
        // check if we have to switch on
        if (QDateTime::currentMSecsSinceEpoch() - lastChangeMs >= durationOffMs) {
            // ok, switch on
            m_localStorage->set(INTERVAL_STATES + key, true);
            state = true;
            m_localStorage->set(INTERVAL_LAST_CHANGES + key, QDateTime::currentMSecsSinceEpoch());
            iDebug() << "Interval switching to" << key << state;
        }
    }

    return state;
}

void CommonScripts::clearInterval(QString key) {
    m_localStorage->unset(INTERVAL_OFF_DURATIONS + key);
    m_localStorage->unset(INTERVAL_ON_DURATIONS + key);
    m_localStorage->unset(INTERVAL_LAST_CHANGES + key);
    m_localStorage->unset(INTERVAL_STATES + key);
}


bool CommonScripts::isWithin(quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo) {
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
