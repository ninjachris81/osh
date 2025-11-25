#include "advancedscripts.h"
#include "3rdparty/sunset.h"

#include <QDateTime>

AdvancedScripts::AdvancedScripts(DatamodelBase *datamodel, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("CommonScripts", datamodel, localStorage, valueManager, actorManager, parent)
{
}

bool AdvancedScripts::applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, double lat, double lng, int timezone, int adjustmentSunrise, int adjustmentSunset, QString tiltThresholdTempFullId, double tiltThresholdTemperature, double closeThresholdTemperature, QString reportTiltModeFullId, QString windowOpenFullId) {
    ShutterActor* shutterActor = static_cast<ShutterActor*>(m_datamodel->actor(shutterFullId));
    EnumValue* shutterModeValue = static_cast<EnumValue*>(m_datamodel->value(shutterModeFullId));
    IntegerValue* reportTiltModeValue = static_cast<IntegerValue*>(m_datamodel->value(reportTiltModeFullId));

    Q_ASSERT(shutterActor != nullptr);
    Q_ASSERT(shutterModeValue != nullptr);

    bool presenceActive = false;
    if (!presenceFullId.isEmpty()) {
        ValueBase* presenceVal = m_datamodel->value(presenceFullId);
        presenceActive = presenceVal->rawValue().toBool();
    }

    bool windowClosed = true;
    if (!windowOpenFullId.isEmpty()) {
        ValueBase* windowVal = m_datamodel->value(windowOpenFullId);
        windowClosed = windowVal->rawValue().toBool();
    }

    QTime utcTime = QDateTime::currentDateTimeUtc().time();
    utcTime = utcTime.addSecs(timezone * 3600);
    SunSet sun(lat, lng, timezone);

    sun.setCurrentDate(QDate::currentDate().year(), QDate::currentDate().month(), QDate::currentDate().day());

    QTime sunrise(0, 0, 0);
    sunrise = sunrise.addSecs((sun.calcSunrise()  + adjustmentSunrise) * 60);

    QTime sunset(0, 0, 0);
    sunset = sunset.addSecs((sun.calcSunset()  + adjustmentSunset) * 60);

    bool isDownTime = isWithin(sunset.hour(), sunset.minute(), sunrise.hour(), sunrise.minute(), utcTime);
    bool isTiltDownOpenState = false;       // should be down, but tilt open
    int shutterTiltMode = SHUTTER_TILT_MODE_NORMAL;

    if (!isDownTime && (tiltThresholdTempFullId != nullptr && !tiltThresholdTempFullId.isEmpty())) {
        DoubleValue* tempValue = static_cast<DoubleValue*>(m_datamodel->value(tiltThresholdTempFullId));
        Q_ASSERT(tempValue != nullptr);

        if (tempValue->rawValue().isValid()) {
            if (tiltThresholdTemperature > 0 && tempValue->rawValue().toDouble() > tiltThresholdTemperature && shutterActor->checkTiltSupport()) {
                isTiltDownOpenState = true;
                shutterTiltMode = SHUTTER_TILT_MODE_TILT;
            }

            if (closeThresholdTemperature > 0 && tempValue->rawValue().toDouble() > closeThresholdTemperature) {
                isDownTime = true;
                shutterTiltMode = SHUTTER_TILT_MODE_CLOSE;
            }
        } else {
            // temp not valid
        }
    }


    if (!shutterModeValue->rawValue().isValid() || (shutterModeValue->rawValue().isValid() && shutterModeValue->rawValue().toInt() == SHUTTER_OPERATION_MODE_AUTO)) {
        if (isDownTime) {
            // down: check is presence active
            if (!presenceActive && windowClosed) {
                if (shutterActor->rawValue().toInt() != SHUTTER_CLOSED) {
                    iDebug() << "Shutter down";
                    publishCmd(shutterActor, actor::ACTOR_CMD_DOWN, "applyShutterLogic");
                } else {
                    iDebug() << "Shutter already down";
                }
            } else {
                iDebug() << "Presence still active or window not closed";
            }
        } else {
            // up: just time-based
            if (shutterActor->rawValue().toInt() != SHUTTER_OPENED) {
                if (isTiltDownOpenState) {
                    // just turn open
                    if (shutterActor->tiltState() == SHUTTER_TILT_CLOSED) {
                        iDebug() << "Turn open";
                        publishCmd(shutterActor, actor::ACTOR_CMD_SHUTTER_TURN_OPEN, "applyShutterLogic");
                    } else {
                        iDebug() << "Already tilted";
                    }
                } else {
                    // full up
                    iDebug() << "Shutter up";
                    publishCmd(shutterActor, actor::ACTOR_CMD_UP, "applyShutterLogic");
                }
            } else if (shutterActor->rawValue().toInt() == SHUTTER_OPENED && isTiltDownOpenState) {
                iDebug() << "Full down open";
                publishCmd(shutterActor, actor::ACTOR_CMD_SHUTTER_FULL_OPEN, "applyShutterLogic");
            } else {
                iDebug() << "Shutter already open";
            }
        }
    } else {
        // set to manual
    }

    if (reportTiltModeValue != nullptr) {
        publishValue(reportTiltModeValue, shutterTiltMode);
    }

    return true;
}
