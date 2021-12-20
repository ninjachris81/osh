#include "commonscripts.h"

#include <QDateTime>

CommonScripts::CommonScripts(QJSEngine *engine, DatamodelBase *datamodel, LocalStorage *localStorage, QObject *parent) : ScriptBase("CommonScripts", parent), m_engine(engine), m_datamodel(datamodel), m_localStorage(localStorage)
{

}

/*
 * Returns true if the function has been called
*/
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

bool CommonScripts::applySwitchLogic(QString lightActorFullId, QString inputSensorFullId, QString motionSensorFullId, QString brightnessSensorFullId, int brightnessThreshold, quint64 triggerTimeoutMs, quint64 motionSensorGracePeriodMs) {
    if (m_datamodel->actors().contains(lightActorFullId) && m_datamodel->values().contains(inputSensorFullId) && m_datamodel->values().contains(motionSensorFullId)) {
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

            if (inputSensor->rawValue() != lastValue && inputSensor->rawValue().toBool()) {
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
                triggerReason = "Default off";
                expectedValue = false;
            }
        }

        // finally set the value
        if (actualValue != expectedValue && expectedValue.isValid()) {
            lightActor->triggerCmd(expectedValue.toBool() ? ACTOR_CMD_ON : ACTOR_CMD_OFF, triggerReason);
        }

        return true;
    } else {
        iWarning() << "Invalid parameters" << lightActorFullId << inputSensorFullId;
        return false;
    }
}
