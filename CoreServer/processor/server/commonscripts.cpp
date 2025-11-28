#include "commonscripts.h"
#include "actor/toggleactor.h"

#include <QDateTime>

#include "helpers.h"


CommonScripts::CommonScripts(DatamodelBase *datamodel, LocalStorage *localStorage, TaskStorage *taskStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("CommonScripts", datamodel, localStorage, taskStorage, valueManager, actorManager, parent)
{
}

bool CommonScripts::initSwitchPresenceLogic(QString presenceId, QString toggleActorId, QString brightnessId, double brightnessThreshold, quint64 switchCooldownPeriodMs) {
    iInfo() << Q_FUNC_INFO;

    BooleanValue* presenceSensor = static_cast<BooleanValue*>(m_datamodel->value(presenceId));
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actor(toggleActorId));
    DoubleValue* brightnessValue = static_cast<DoubleValue*>(m_datamodel->value(brightnessId));

    Q_ASSERT(presenceSensor != nullptr);
    Q_ASSERT(toggleActor != nullptr);
    Q_ASSERT(brightnessValue != nullptr);

    m_localStorage->setObject("initSwitchPresenceLogic", "toggleActor", presenceSensor->fullId(), toggleActor);
    m_localStorage->setObject("initSwitchPresenceLogic", "brightnessValue", presenceSensor->fullId(), brightnessValue);
    m_localStorage->set("initSwitchPresenceLogic", "brightnessThreshold", presenceSensor->fullId(), brightnessThreshold);
    m_localStorage->set("initSwitchPresenceLogic", "switchCooldownPeriodMs", presenceSensor->fullId(), switchCooldownPeriodMs);

    Helpers::safeConnect(presenceSensor, &ValueBase::valueChanged, this, &CommonScripts::onInitSwitchPresenceLogic_presenceValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchPresenceLogic_presenceValueChanged()));

    return true;
}

/*
 *  ONLY handles turn ON logic
 *  OFF is handled by apply
 */
void CommonScripts::onInitSwitchPresenceLogic_presenceValueChanged() {
    iDebug() << Q_FUNC_INFO;

    BooleanValue* presenceSensor = static_cast<BooleanValue*>(sender());
    _onInitSwitchPresenceLogic_presenceValueChanged(presenceSensor);
}

void CommonScripts::_onInitSwitchPresenceLogic_presenceValueChanged(BooleanValue *presenceSensor) {
    if (presenceSensor->rawValue().isValid() && presenceSensor->rawValue().toBool()) {
        // presence active, check if light is on
        ToggleActor* toggleActor = static_cast<ToggleActor*>(m_localStorage->getObject("initSwitchPresenceLogic", "toggleActor", presenceSensor->fullId()));
        if (!toggleActor->rawValue().toBool()) {
            // next, check brightness
            DoubleValue* brightnessValue = static_cast<DoubleValue*>(m_localStorage->getObject("initSwitchPresenceLogic", "brightnessValue", presenceSensor->fullId()));
            double brightnessThreshold = m_localStorage->get("initSwitchPresenceLogic", "brightnessThreshold", presenceSensor->fullId()).toDouble();

            if (brightnessValue->rawValue().isValid() && brightnessValue->rawValue().toDouble() < brightnessThreshold) {

                qint64 switchCooldownPeriodMs = m_localStorage->get("initSwitchPresenceLogic", "switchCooldownPeriodMs", presenceSensor->fullId(), 0).toLongLong();
                qint64 lastSwitchOff = m_localStorage->get("initSwitchLogic", "lastSwitchOff", toggleActor->fullId(), 0).toLongLong();

                if (QDateTime::currentMSecsSinceEpoch() > (lastSwitchOff + switchCooldownPeriodMs)) {
                    // ok, it's too dark, light is off and presence detected -> switch it ON
                    publishCmd(toggleActor, ACTOR_CMDS::ACTOR_CMD_ON, true, "presence");
                } else {
                    // user just pressed turned it OFF, so ignore this one
                }
            }
        }
    }
}

/*
 *
 */
bool CommonScripts::applySwitchPresenceLogic(QString presenceId) {
    iDebug() << Q_FUNC_INFO;

    BooleanValue* presenceSensor = static_cast<BooleanValue*>(m_datamodel->value(presenceId));
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_localStorage->getObject("initSwitchPresenceLogic", "toggleActor", presenceSensor->fullId()));

    Q_ASSERT(presenceSensor != nullptr);
    Q_ASSERT(toggleActor != nullptr);

    if (presenceSensor->rawValue().isValid() ) {
        if (presenceSensor->rawValue().toBool()) {
            _onInitSwitchPresenceLogic_presenceValueChanged(presenceSensor);
        } else {
            if (toggleActor->rawValue().toBool()) {
                publishCmd(toggleActor, ACTOR_CMDS::ACTOR_CMD_OFF, false, "presence");
            }
        }
    }

    return true;
}

bool CommonScripts::initSwitchLogic(QString lightRelayActorFullIds, QString inputSensorFullId, QString toggleActorFullId) {
    iInfo() << lightRelayActorFullIds << inputSensorFullId << toggleActorFullId;

    BooleanValue* inputSensor = static_cast<BooleanValue*>(m_datamodel->value(inputSensorFullId));
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actor(toggleActorFullId));

    Q_ASSERT(inputSensor != nullptr);
    Q_ASSERT(toggleActor != nullptr);

    m_localStorage->setObject("initSwitchLogic", "toggleActor", inputSensor->fullId(), toggleActor);
    Helpers::safeConnect(inputSensor, &BooleanValue::valueChanged, this, &CommonScripts::onInitSwitchLogic_inputSensorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_inputSensorValueChanged()));
    Helpers::safeConnect(toggleActor, &ToggleActor::valueChanged, this, &CommonScripts::onInitSwitchLogic_toggleActorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic_toggleActorValueChanged()));

    quint8 index = 0;
    for (QString lightRelayActorFullId : lightRelayActorFullIds.split("|", QString::SkipEmptyParts)) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_datamodel->actor(lightRelayActorFullId));
        Q_ASSERT(lightRelayActor != nullptr);
        m_localStorage->setObject("initSwitchLogic", "lightRelay", toggleActor->fullId() + "_" + index, lightRelayActor);
        index++;
    }

    return true;
}

void CommonScripts::onInitSwitchLogic_inputSensorValueChanged() {
    iDebug() << Q_FUNC_INFO;

    BooleanValue* inputSensor = static_cast<BooleanValue*>(sender());
    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_localStorage->getObject("initSwitchLogic", "toggleActor", inputSensor->fullId()));

    bool lastInputVal = m_localStorage->get("initSwitchLogic", "lastVal", inputSensor->fullId(), false).toBool();
    if (lastInputVal != inputSensor->rawValue().toBool()) {
        m_localStorage->set("initSwitchLogic", "lastVal", inputSensor->fullId(), inputSensor->rawValue().toBool());

        if (inputSensor->rawValue().isValid() && inputSensor->rawValue().toBool()) {
            // toggle controller is in server, so just emit
            //Q_EMIT(toggleActor->requestToggle());
            publishCmd(toggleActor, ACTOR_CMDS::ACTOR_CMD_TOGGLE, "input sensor");

            if (!toggleActor->rawValue().toBool()) {
                m_localStorage->set("initSwitchLogic", "lastSwitchOff", toggleActor->fullId(), QDateTime::currentMSecsSinceEpoch());       // for initSwitchPresenceLogic and applySwitchPresenceLogic
            }
        }
    }
}

void CommonScripts::onInitSwitchLogic_toggleActorValueChanged() {
    ToggleActor* toggleActor = static_cast<ToggleActor*>(sender());

    for (quint8 index = 0; index<255; index++) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_localStorage->getObject("initSwitchLogic", "lightRelay", toggleActor->fullId() + "_" + index));
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

        publishCmd(lightRelayActor, toggleActor->rawValue().toBool() ? ACTOR_CMDS::ACTOR_CMD_ON : ACTOR_CMDS::ACTOR_CMD_OFF, "toggle");
    }
}


bool CommonScripts::initSwitchLogic2(QString lightRelayActorFullIds, QString toggleActorFullId) {
    iInfo() << lightRelayActorFullIds << toggleActorFullId;

    ToggleActor* toggleActor = static_cast<ToggleActor*>(m_datamodel->actor(toggleActorFullId));

    Q_ASSERT(toggleActor != nullptr);

    Helpers::safeConnect(toggleActor, &ToggleActor::valueChanged, this, &CommonScripts::onInitSwitchLogic2_toggleActorValueChanged, SIGNAL(valueChanged()), SLOT(onInitSwitchLogic2_toggleActorValueChanged()));

    quint8 index = 0;
    for (QString lightRelayActorFullId : lightRelayActorFullIds.split("|", QString::SkipEmptyParts)) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_datamodel->actor(lightRelayActorFullId));
        Q_ASSERT(lightRelayActor != nullptr);
        m_localStorage->setObject("initSwitchLogic", "lightRelay", toggleActor->fullId() + "_" + index, lightRelayActor);
        index++;
    }

    return true;
}


void CommonScripts::onInitSwitchLogic2_toggleActorValueChanged() {
    ToggleActor* toggleActor = static_cast<ToggleActor*>(sender());

    for (quint8 index = 0; index<255; index++) {
        DigitalActor* lightRelayActor = static_cast<DigitalActor*>(m_localStorage->getObject("initSwitchLogic", "lightRelay", toggleActor->fullId() + "_" + index));
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

        publishCmd(lightRelayActor, toggleActor->rawValue().toBool() ? ACTOR_CMDS::ACTOR_CMD_ON : ACTOR_CMDS::ACTOR_CMD_OFF, "toggle");
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
            publishCmd(toggleActor, ACTOR_CMDS::ACTOR_CMD_TOGGLE, "Timeout");
        } else {
            // hmm, already off
        }
    }

    return true;
}

bool CommonScripts::applyTempValveLogic(QString tempFullId, QString tempTargetFullId, QString tempValveActorFullId, int adjustIntervalMs, double fullDeltaThresholdTemp, int factorIntervalMs) {
    if (m_datamodel->actors().contains(tempValveActorFullId)) {
        QString valveKey = "temp_valve_" + tempValveActorFullId;
        qlonglong lastAdjustMs = m_localStorage->get("applyTempValveLogic", "lastAdjust", tempValveActorFullId, 0).toULongLong();
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
                                tempValve->triggerCmd(ACTOR_CMDS::ACTOR_CMD_ON, "Always on");
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

                    m_localStorage->set("applyTempValveLogic", "lastAdjust", tempValveActorFullId, QDateTime::currentMSecsSinceEpoch());
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
            m_localStorage->set("applyTempValveLogic", "lastAdjust", tempValveActorFullId, QDateTime::currentMSecsSinceEpoch());
        } else {
            // check interval
            bool targetValveState = getIntervalState(valveKey);

            if (tempValve->rawValue().toBool() != targetValveState) {
                tempValve->triggerCmd(targetValveState ? ACTOR_CMDS::ACTOR_CMD_ON : ACTOR_CMDS::ACTOR_CMD_OFF, "Interval timeout");
            }

            return true;
        }
    } else {
        iWarning() << "Invalid parameters" << tempValveActorFullId;
        return false;
    }

    return false;
}

bool CommonScripts::initPresenceLogic(QString radarId, QString pirId, QString presenceId) {
    iInfo() << Q_FUNC_INFO;

    BooleanValue* presenceVal = static_cast<BooleanValue*>(m_datamodel->value(presenceId));
    Q_ASSERT(presenceVal!=nullptr);

    publishValue(presenceVal, false);       // overwrite retain

    if (!radarId.isEmpty()) {
        BooleanValue* radarVal = static_cast<BooleanValue*>(m_datamodel->value(radarId));
        Q_ASSERT(radarVal!=nullptr);
        Helpers::safeConnect(radarVal, &ValueBase::valueChanged, this, &CommonScripts::onInitPresenceLogic_radarValueChanged, SIGNAL(valueChanged()), SLOT(onInitPresenceLogic_radarValueChanged()));
        m_localStorage->setObject("initPresenceLogic", "radarPresence", radarVal->fullId(), presenceVal);
        m_localStorage->set("initPresenceLogic", "hasRadar", presenceVal->fullId(), true);
    }

    if (!pirId.isEmpty()) {
        ValueBase* pirVal = static_cast<BooleanValue*>(m_datamodel->value(pirId));
        Q_ASSERT(pirVal!=nullptr);
        Helpers::safeConnect(pirVal, &ValueBase::valueChanged, this, &CommonScripts::onInitPresenceLogic_pirValueChanged, SIGNAL(valueChanged()), SLOT(onInitPresenceLogic_pirValueChanged()));
        m_localStorage->setObject("initPresenceLogic", "pirPresence", pirVal->fullId(), presenceVal);
        m_localStorage->set("initPresenceLogic", "hasPir", presenceVal->fullId(), true);
    }

    return true;
}

void CommonScripts::onInitPresenceLogic_radarValueChanged() {
    iDebug() << Q_FUNC_INFO;
    onInitPresenceLogic_valueChanged(sender(), "radarPresence", "radar");
}

void CommonScripts::onInitPresenceLogic_pirValueChanged() {
    iDebug() << Q_FUNC_INFO;
    onInitPresenceLogic_valueChanged(sender(), "pirPresence", "pir");
}

void CommonScripts::onInitPresenceLogic_valueChanged(QObject *sender, QString presenceKey, QString valueKey) {
    iInfo() << Q_FUNC_INFO;

    BooleanValue* sensorVal = static_cast<BooleanValue*>(sender);
    BooleanValue* presenceVal = static_cast<BooleanValue*>(m_localStorage->getObject("initPresenceLogic", presenceKey, sensorVal->fullId()));

    if (sensorVal->rawValue().isValid() && sensorVal->rawValue().toBool()) {
        m_localStorage->set("initPresenceLogic", valueKey, presenceVal->fullId(), true);
    } else {
        m_localStorage->set("initPresenceLogic", valueKey, presenceVal->fullId(), false);
    }
    applyPresenceLogic(presenceVal->fullId(), 60000);           // call with 60 sec, but normal interval will be lower anyways
}

bool CommonScripts::applyPresenceLogic(QString presenceId, qint32 timeoutMs) {
    iInfo() << Q_FUNC_INFO;

    BooleanValue* presenceVal = static_cast<BooleanValue*>(m_datamodel->value(presenceId));
    Q_ASSERT(presenceVal!=nullptr);

    bool hasRadar = m_localStorage->get("initPresenceLogic", "hasRadar", presenceVal->fullId(), false).toBool();
    bool isRadar = m_localStorage->get("initPresenceLogic", "radar", presenceVal->fullId(), false).toBool();

    bool hasPir = m_localStorage->get("initPresenceLogic", "hasPir", presenceVal->fullId(), false).toBool();
    bool isPir = m_localStorage->get("initPresenceLogic", "pir", presenceVal->fullId(), false).toBool();

    if ((hasRadar && isRadar) || (hasPir && isPir)) {
        m_localStorage->set("initPresenceLogic", "lastTs", presenceVal->fullId(), QDateTime::currentMSecsSinceEpoch());

        if (!presenceVal->rawValue().toBool()) {
            publishValue(presenceVal, true);
        }
    } else {
        qint64 lastActive = m_localStorage->get("initPresenceLogic", "lastTs", presenceVal->fullId(), 0).toLongLong();
        if (lastActive > 0 && QDateTime::currentMSecsSinceEpoch() - lastActive > timeoutMs) {
            // switch off
            publishValue(presenceVal, false);
            m_localStorage->set("initPresenceLogic", "lastTs", presenceVal->fullId(), 0);
        }
    }

    return true;
}

bool CommonScripts::applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo) {
    ShutterActor* shutterActor = static_cast<ShutterActor*>(m_datamodel->actor(shutterFullId));
    EnumValue* shutterMode = static_cast<EnumValue*>(m_datamodel->value(shutterModeFullId));

    Q_ASSERT(shutterActor != nullptr);
    Q_ASSERT(shutterMode != nullptr);

    bool presenceActive = false;
    if (!presenceFullId.isEmpty()) {
        ValueBase* presenceVal = m_datamodel->value(presenceFullId);
        presenceActive = presenceVal->rawValue().toBool();
    }

    bool isDownTime = isWithin(hourFrom, minuteFrom, hourTo, minuteTo);

    if (shutterMode->rawValue().isValid() && shutterMode->rawValue().toInt() == SHUTTER_OPERATION_MODE_AUTO) {
        if (isDownTime) {
            // down: check is presence active
            if (!presenceActive && shutterActor->rawValue().toInt() != SHUTTER_CLOSED) {
                publishCmd(shutterActor, ACTOR_CMDS::ACTOR_CMD_DOWN, "applyShutterLogic");
            } else {
                iDebug() << "Room still active - pausing shutter actions";
            }
        } else {
            // up: just time-based
            if (shutterActor->rawValue().toInt() != SHUTTER_OPENED) {
                publishCmd(shutterActor, ACTOR_CMDS::ACTOR_CMD_UP, "applyShutterLogic");
            }
        }
    } else {
        // set to manual
    }

    return true;
}

bool CommonScripts::initDoorRingLogic(QString inputSensorFullId, QString doorRingActorFullId, int retriggerTimeout) {
    BooleanValue* inputSensor = static_cast<BooleanValue*>(m_datamodel->value(inputSensorFullId));
    DigitalActor* ringActor = static_cast<DigitalActor*>(m_datamodel->actor(doorRingActorFullId));

    Q_ASSERT(inputSensor != nullptr);
    Q_ASSERT(ringActor != nullptr);

    m_localStorage->setObject("initDoorRingLogic", "ringActor", inputSensor->fullId(), ringActor);
    m_localStorage->set("initDoorRingLogic", "ringTimeout", inputSensor->fullId(), retriggerTimeout);

    Helpers::safeConnect(inputSensor, &BooleanValue::valueChanged, this, &CommonScripts::onInitDoorRingLogic_inputSensorValueChanged, SIGNAL(valueChanged()), SLOT(onInitDoorRingLogic_inputSensorValueChanged()));

    return true;
}

void CommonScripts::onInitDoorRingLogic_inputSensorValueChanged() {
    iDebug() << Q_FUNC_INFO;
    BooleanValue* inputSensor = static_cast<BooleanValue*>(sender());
    DigitalActor* ringActor = static_cast<DigitalActor*>(m_localStorage->getObject("initDoorRingLogic", "ringActor", inputSensor->fullId()));

    bool lastInputVal = m_localStorage->get("initDoorRingLogic", "lastVal", inputSensor->fullId(), false).toBool();
    int ringTimeout = m_localStorage->get("initDoorRingLogic", "ringTimeout", inputSensor->fullId(), 3000).toInt();
    quint64 lastRing = m_localStorage->get("initDoorRingLogic", "lastRing", inputSensor->fullId(), 0).toLongLong();

    if (lastRing == 0 || QDateTime::currentMSecsSinceEpoch() - lastRing > ringTimeout) {
        if (lastInputVal != inputSensor->rawValue().toBool()) {     // on toggle true
            setTimeout(ringActor->fullId());

            if (inputSensor->rawValue().isValid() && inputSensor->rawValue().toBool() && !ringActor->rawValue().toBool()) {
                publishCmd(ringActor, ACTOR_CMDS::ACTOR_CMD_ON, "input sensor");
                m_localStorage->set("initDoorRingLogic", "lastVal", inputSensor->fullId(), true);
                m_localStorage->set("initDoorRingLogic", "lastRing", inputSensor->fullId(), QDateTime::currentMSecsSinceEpoch());
            }
        }
    } else {
        // last ring too recent
    }
}

bool CommonScripts::applyDoorRingTimeoutLogic(QString doorRingActorFullId, quint64 triggerTimeoutMs) {
    return isTimeout(doorRingActorFullId, triggerTimeoutMs, true);
}

bool CommonScripts::initPlaySoundOnValue(QString valueEventId, QString playValue, QString soundActorId, QString soundValue) {
    return initPlaySoundOnValue2(valueEventId, playValue, "", soundActorId, soundValue);
}

bool CommonScripts::initPlaySoundOnValue2(QString valueEventId, QString playValue, QString stopValue, QString soundActorId, QString soundValue) {
    iInfo() << Q_FUNC_INFO;
    ValueBase *value = m_datamodel->value(valueEventId);
    if (value == nullptr) {
        // could be actor or value
        value = m_datamodel->actor(valueEventId);
    }
    AudioPlaybackActor *playbackActor = static_cast<AudioPlaybackActor*>(m_datamodel->actor(soundActorId));

    Q_ASSERT(value != nullptr);
    Q_ASSERT(playbackActor != nullptr);

    if (soundValue.isEmpty()) {
        if (playbackActor->audioUrl().isEmpty()) {
            iWarning() << "Audio actors must have static url value set if soundValue is empty" << playbackActor->fullId();
            Q_ASSERT(false);
        } else {
            // play static url
            iDebug() << "Using static Url" << playbackActor->audioUrl();
        }
    }

    m_taskStorage->registerExecution(value, [this, value, playValue, stopValue, soundValue, playbackActor](QVariantList params) {

        QVariant playValueVar = playValue;
        QVariant stopValueVar = stopValue;

        if (playValueVar.convert(value->rawValue().type())) {
            if (value->rawValue() == playValue) {
                iInfo() << "Play Trigger";

                if (!soundValue.isEmpty()) {
                    StringValue *urlValue = static_cast<StringValue*>(m_datamodel->value(playbackActor->audioUrlId()));
                    Q_ASSERT(urlValue != nullptr);
                    iDebug() << "Setting url" << soundValue;
                    publishValue(urlValue, soundValue);
                } else {
                    // playback static url
                    iDebug() << "Playback static url";
                }

                publishCmd(playbackActor, ACTOR_CMDS::ACTOR_CMD_START, "event play playback");
            }
        } else {
            iWarning() << "Failed to convert play value to target type";
        }

        if (stopValueVar.convert(value->rawValue().type())) {
            if (value->rawValue() == stopValue) {
                iInfo() << "Stop Trigger";
                publishCmd(playbackActor, ACTOR_CMDS::ACTOR_CMD_STOP, "event stop playback");
            }
        } else {
            iWarning() << "Failed to convert stop value to target type";
        }


    });

    Helpers::safeConnect(value, &ValueBase::valueChanged, this, &CommonScripts::onInitPlaySoundOnValue_valueChanged, SIGNAL(valueChanged()), SLOT(onInitPlaySoundOnValue_valueChanged()));

    return true;
}

void CommonScripts::onInitPlaySoundOnValue_valueChanged() {
    iInfo() << Q_FUNC_INFO;
    m_taskStorage->triggerExecution(sender(), {});
}

bool CommonScripts::initPlaySoundOnCmd(QString taskId, QString actorId, int cmdValue, QString soundActorId, QString soundValue) {
    iInfo() << Q_FUNC_INFO;

    ActorBase* actor = m_actorManager->getActor(actorId);
    Q_ASSERT(actor != nullptr);

    QList<AudioPlaybackActor*> playbackActors;
    for (QString playbackActorFullId : soundActorId.split("|", QString::SkipEmptyParts)) {
        iInfo() << "Register" << playbackActorFullId;
        AudioPlaybackActor *playbackActor = static_cast<AudioPlaybackActor*>(m_datamodel->actor(playbackActorFullId));
        Q_ASSERT(playbackActor != nullptr);
        playbackActors << playbackActor;
    }

    m_taskStorage->registerExecution(actor, [this, taskId, cmdValue, soundValue, playbackActors](QVariantList params) {
        if (cmdValue == params.at(0).toInt()) {
            iInfo() << "Is target cmd, proceed";

            // avoid multiple callbacks in a row
            if (QDateTime::currentMSecsSinceEpoch() - m_localStorage->get("initPlaySoundOnCmd", "lastTrigger", taskId).toLongLong() > 2000) {
                m_localStorage->set("initPlaySoundOnCmd", "lastTrigger", taskId, QDateTime::currentMSecsSinceEpoch());

                for (AudioPlaybackActor *playbackActor : playbackActors) {
                    if (!soundValue.isEmpty() && !playbackActor->audioUrlId().isEmpty()) {
                        StringValue *urlValue = static_cast<StringValue*>(m_datamodel->value(playbackActor->audioUrlId()));
                        iDebug() << "Setting url" << soundValue;
                        publishValue(urlValue, soundValue);
                    } else {
                        // playback static url
                        iDebug() << "Playback static url";
                    }

                    iInfo() << "Start playback" << playbackActor->fullId();
                    publishCmd(playbackActor, ACTOR_CMDS::ACTOR_CMD_START, "event play playback");
                }
            } else {
                iDebug() << "Method called too fast in a row";
            }
        }
    });

    Helpers::safeConnect(actor, &ActorBase::cmdTriggered, this, &CommonScripts::onInitPlaySoundOnCmd_triggeredCmd, SIGNAL(cmdTriggered(ACTOR_CMDS)), SLOT(onInitPlaySoundOnCmd_triggeredCmd(ACTOR_CMDS)));

    return true;
}

void CommonScripts::onInitPlaySoundOnCmd_triggeredCmd(ACTOR_CMDS cmd) {
    iInfo() << Q_FUNC_INFO;
    m_taskStorage->triggerExecution(sender(), { QVariant((int) cmd) });
}
