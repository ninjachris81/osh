#include "commonscripts.h"
#include "actor/toggleactor.h"

#include <QDateTime>

#include "helpers.h"


CommonScripts::CommonScripts(DatamodelBase *datamodel, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("CommonScripts", datamodel, localStorage, valueManager, actorManager, parent)
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
        ActorBase* lightActor = m_datamodel->actor(lightActorFullId);
        ValueBase* inputSensor = m_datamodel->value(inputSensorFullId);
        ValueBase* motionSensor = m_datamodel->value(motionSensorFullId);
        ValueBase* brightnessSensor = m_datamodel->value(brightnessSensorFullId);

        QVariant actualValue = lightActor->rawValue();
        QVariant expectedValue;

        //QString lastTsMotionSensorKey = "lastTs_" + motionSensorFullId;
        QString graceMotionSensorKey = "grace_" + motionSensorFullId;
        //QString lastTsInputKey = "lastTs_" + inputSensorFullId;
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
            clearTimeout(motionSensorFullId);
            clearTimeout(inputSensorFullId);
            m_localStorage->set(graceMotionSensorKey, QDateTime::currentMSecsSinceEpoch());
        } else {
            // update last values
            if (brightnessSensor->isValid() && brightnessSensor->rawValue().toInt() < brightnessThreshold) {
                if (motionSensor->isValid() && motionSensor->rawValue().toBool() && (QDateTime::currentMSecsSinceEpoch() - m_localStorage->get(graceMotionSensorKey, 0).toULongLong() > motionSensorGracePeriodMs)) {
                    setTimeout(motionSensorFullId);
                    triggerReason = "Motion sensor";
                }
            }

            if (inputSensor->isValid() && inputTriggered) {
                setTimeout(inputSensorFullId);
                triggerReason = "Input trigger";
            }

            quint64 lastContact = qMax(getTimeout(motionSensorFullId), getTimeout(inputSensorFullId));

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

bool CommonScripts::initSwitchLogic(QString lightRelayActorFullIds, QString inputSensorFullId, QString toggleActorFullId) {
    iDebug() << lightRelayActorFullIds << inputSensorFullId << toggleActorFullId;

    BooleanValue* inputSensor = static_cast<BooleanValue*>(m_datamodel->value(inputSensorFullId));
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actor(toggleActorFullId));

    Q_ASSERT(inputSensor != nullptr);
    Q_ASSERT(toggleActor != nullptr);

    m_localStorage->setObject("switch_toggle_actor_" + inputSensorFullId, toggleActor);
    Helpers::safeConnect(inputSensor, &BooleanValue::valueChanged, this, &CommonScripts::onInitSwitchLogic_inputSensorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_inputSensorValueChanged()));
    Helpers::safeConnect(toggleActor, &ToggleActor::valueChanged, this, &CommonScripts::onInitSwitchLogic_toggleActorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_toggleActorValueChanged()));

    quint8 index = 0;
    for (QString lightRelayActorFullId : lightRelayActorFullIds.split("|", QString::SkipEmptyParts)) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_datamodel->actor(lightRelayActorFullId));
        Q_ASSERT(lightRelayActor != nullptr);
        m_localStorage->setObject("switch_light_relay_" + toggleActorFullId + "_" + index, lightRelayActor);
        index++;
    }

    return true;
}

void CommonScripts::onInitSwitchLogic_inputSensorValueChanged() {
    iDebug() << Q_FUNC_INFO;

    BooleanValue* inputSensor = static_cast<BooleanValue*>(sender());
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_localStorage->getObject("switch_toggle_actor_" + inputSensor->fullId()));

    QString lastInputValKey = "lastVal_" + inputSensor->fullId();
    bool lastInputVal = m_localStorage->get(lastInputValKey, false).toBool();
    if (lastInputVal != inputSensor->rawValue().toBool()) {
        m_localStorage->set(lastInputValKey, inputSensor->rawValue().toBool());

        if (inputSensor->rawValue().isValid() && inputSensor->rawValue().toBool()) {
            // toggle controller is in server, to just emit
            //Q_EMIT(toggleActor->requestToggle());
            publishCmd(toggleActor, actor::ACTOR_CMD_TOGGLE, "input sensor");
        }
    }
}

void CommonScripts::onInitSwitchLogic_toggleActorValueChanged() {
    ToggleActor* toggleActor = static_cast<ToggleActor*>(sender());

    for (quint8 index = 0; index<255; index++) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_localStorage->getObject("switch_light_relay_" + toggleActor->fullId() + "_" + index));
        if (lightRelayActor == nullptr) {
            break;
        }

        //QString lastTsInputKey = "lastToggleTs_" + toggleActor->fullId();

        if (toggleActor->rawValue().toBool()) {
            setTimeout(toggleActor->fullId());
            //m_localStorage->set(lastTsInputKey, QDateTime::currentMSecsSinceEpoch());
        } else {
            clearTimeout(toggleActor->fullId());
            //m_localStorage->unset(lastTsInputKey);
        }

        publishCmd(lightRelayActor, toggleActor->rawValue().toBool() ? actor::ACTOR_CMD_ON : actor::ACTOR_CMD_OFF, "toggle");
    }
}


bool CommonScripts::applySwitchTimeoutLogic(QString toggleActorFullId, quint64 triggerTimeoutMs) {
    QString lastTsInputKey = "lastToggleTs_" + toggleActorFullId;

    // check for timeout
    if (isTimeout(toggleActorFullId, triggerTimeoutMs, true)) {
        ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actor(toggleActorFullId));

        if (toggleActor->rawValue().toBool()) {
            // toggle controller is in server, to just emit
            //Q_EMIT(toggleActor->requestToggle());
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
        ActorBase* tempValve = m_datamodel->actor(tempValveActorFullId);

        if (lastAdjustMs == 0 || QDateTime::currentMSecsSinceEpoch() - lastAdjustMs > adjustIntervalMs) {
            if (m_datamodel->values().contains(tempFullId) && m_datamodel->values().contains(tempTargetFullId)) {
                ValueBase* temp = m_datamodel->value(tempFullId);
                ValueBase* targetTemp = m_datamodel->value(tempTargetFullId);

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
    ValueBase* radarVal = m_datamodel->value(radarFullId);
    ValueBase* pirVal = m_datamodel->value(pirFullId);
    ValueBase* motionVal = m_datamodel->value(motionFullId);

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
    ShutterActor* shutterActor = static_cast<ShutterActor*>(m_datamodel->actor(shutterFullId));
    EnumValue* shutterMode = static_cast<EnumValue*>(m_datamodel->value(shutterModeFullId));

    Q_ASSERT(shutterActor != nullptr);
    Q_ASSERT(shutterMode != nullptr);

    bool motionActive = false;
    if (!motionFullId.isEmpty()) {
        ValueBase* motionVal = m_datamodel->value(motionFullId);
        motionActive = motionVal->rawValue().toBool();
    }

    bool isDownTime = isWithin(hourFrom, minuteFrom, hourTo, minuteTo);

    if (shutterMode->rawValue().isValid() && shutterMode->rawValue().toInt() == SHUTTER_OPERATION_MODE_AUTO) {
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
    } else {
        // set to manual
    }

    return true;
}

bool CommonScripts::initDoorRingLogic(QString inputSensorFullId, QString doorRingActorFullId) {
    BooleanValue* inputSensor = static_cast<BooleanValue*>(m_datamodel->value(inputSensorFullId));
    DigitalActor* ringActor = static_cast<DigitalActor*>(m_datamodel->actor(doorRingActorFullId));

    Q_ASSERT(inputSensor != nullptr);
    Q_ASSERT(ringActor != nullptr);

    m_localStorage->setObject("door_ring_actor_" + inputSensorFullId, ringActor);
    Helpers::safeConnect(inputSensor, &BooleanValue::valueChanged, this, &CommonScripts::onInitDoorRingLogic_inputSensorValueChanged, SIGNAL(valueChanged()), SLOT(onInitDoorRingLogic_inputSensorValueChanged()));

    return true;
}

void CommonScripts::onInitDoorRingLogic_inputSensorValueChanged() {
    iDebug() << Q_FUNC_INFO;
    BooleanValue* inputSensor = static_cast<BooleanValue*>(sender());
    DigitalActor* ringActor = static_cast<DigitalActor*>(m_localStorage->getObject("door_ring_actor_" + inputSensor->fullId()));

    QString lastInputValKey = "lastVal_" + inputSensor->fullId();
    bool lastInputVal = m_localStorage->get(lastInputValKey, false).toBool();
    if (lastInputVal != inputSensor->rawValue().toBool()) {     // on toggle true
        setTimeout(ringActor->fullId());

        if (inputSensor->rawValue().isValid() && inputSensor->rawValue().toBool() && !ringActor->rawValue().toBool()) {
            publishCmd(ringActor, actor::ACTOR_CMD_ON, true, "input sensor");
        }
    }

}

bool CommonScripts::applyDoorRingTimeoutLogic(QString doorRingActorFullId, quint64 triggerTimeoutMs) {
    return isTimeout(doorRingActorFullId, triggerTimeoutMs, true);
}

bool CommonScripts::initPlaySoundOnEvent(QString valueEventId, QVariant playValue, QString soundActorId, QString soundValue) {
    return initPlaySoundOnEvent2(valueEventId, playValue, QVariant(), soundActorId, soundValue);
}

bool CommonScripts::initPlaySoundOnEvent2(QString valueEventId, QVariant playValue, QVariant stopValue, QString soundActorId, QString soundValue) {
    iInfo() << Q_FUNC_INFO;
    ValueBase *value = m_datamodel->value(valueEventId);
    if (value == nullptr) {
        // could be actor or value
        value = m_datamodel->actor(valueEventId);
    }
    AudioPlaybackActor *playbackActor = static_cast<AudioPlaybackActor*>(m_datamodel->actor(soundActorId));
    StringValue *urlValue = static_cast<StringValue*>(m_datamodel->value(playbackActor->audioUrlId()));

    Q_ASSERT(value != nullptr);
    Q_ASSERT(playbackActor != nullptr);

    m_localStorage->set("initPlaySoundOnEvent_playValue_" + value->fullId(), playValue);
    m_localStorage->set("initPlaySoundOnEvent_stopValue_" + value->fullId(), stopValue);
    m_localStorage->setObject("initPlaySoundOnEvent_soundActorId_" + value->fullId(), playbackActor);
    if (!soundValue.isEmpty()) {
        m_localStorage->set("initPlaySoundOnEvent_soundValue_" + value->fullId(), soundValue);
    } else if (soundValue.isEmpty() && playbackActor->audioUrl().isEmpty()) {
        iWarning() << "Audio actors must have static url value set if soundValue is empty" << playbackActor->fullId();
        Q_ASSERT(false);
    }

    if (urlValue == nullptr) {
        // use static url of playback actor
        if (playbackActor->audioUrl().isEmpty()) {
            iWarning() << "Audio actors must have either url value, or static url set" << playbackActor->fullId();
            Q_ASSERT(false);
        }
    } else {
        m_localStorage->setObject("initPlaySoundOnEvent_urlValue_" + value->fullId(), urlValue);
    }

    Helpers::safeConnect(value, &ValueBase::valueChanged, this, &CommonScripts::onInitPlaySoundOnEvent_valueChanged, SIGNAL(valueChanged()), SLOT(onInitPlaySoundOnEvent_valueChanged()));

    return true;
}

void CommonScripts::onInitPlaySoundOnEvent_valueChanged() {
    iInfo() << Q_FUNC_INFO;

    ValueBase* value = static_cast<ValueBase*>(sender());
    QVariant playValue = m_localStorage->get("initPlaySoundOnEvent_playValue_" + value->fullId());
    QVariant stopValue = m_localStorage->get("initPlaySoundOnEvent_stopValue_" + value->fullId());

    if (playValue.convert(value->rawValue().type())) {
        AudioPlaybackActor *playbackActor = static_cast<AudioPlaybackActor*>(m_localStorage->getObject("initPlaySoundOnEvent_soundActorId_" + value->fullId()));

        if (value->rawValue() == playValue) {
            iInfo() << "Play Trigger";

            if (!m_localStorage->contains("initPlaySoundOnEvent_soundValue_" + value->fullId())) {
                // playback static url
                iDebug() << "Playback static url";
            } else {
                QString soundValue = m_localStorage->get("initPlaySoundOnEvent_soundValue_" + value->fullId()).toString();
                StringValue *urlValue = static_cast<StringValue*>(m_localStorage->getObject("initPlaySoundOnEvent_urlValue_" + value->fullId()));
                iDebug() << "Setting url" << soundValue;
                publishValue(urlValue, soundValue);
            }

            publishCmd(playbackActor, actor::ACTOR_CMD_START, "event play playback");
        } else if (value->rawValue() == stopValue) {
            publishCmd(playbackActor, actor::ACTOR_CMD_STOP, "event stop playback");
        }
    } else {
        iWarning() << "Failed to convert to target type";
    }
}

