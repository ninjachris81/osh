#include "advancedscripts.h"
#include "3rdparty/sunset.h"

#include <QDateTime>

AdvancedScripts::AdvancedScripts(DatamodelBase *datamodel, LocalStorage *localStorage, ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent) : ScriptBase("CommonScripts", datamodel, localStorage, valueManager, actorManager, parent)
{
}

bool AdvancedScripts::applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, double lat, double lng, int timezone) {
    ShutterActor* shutterActor = static_cast<ShutterActor*>(m_datamodel->actor(shutterFullId));
    EnumValue* shutterMode = static_cast<EnumValue*>(m_datamodel->value(shutterModeFullId));

    Q_ASSERT(shutterActor != nullptr);
    Q_ASSERT(shutterMode != nullptr);

    bool presenceActive = false;
    if (!presenceFullId.isEmpty()) {
        ValueBase* presenceVal = m_datamodel->value(presenceFullId);
        presenceActive = presenceVal->rawValue().toBool();
    }

    SunSet sun(lat, lng, timezone);

    sun.setCurrentDate(QDate::currentDate().year(), QDate::currentDate().month() + 5, QDate::currentDate().day());

    QTime sunrise(0, 0, 0);
    sunrise = sunrise.addSecs(sun.calcSunrise() * 60);

    QTime sunset(0, 0, 0);
    sunset = sunset.addSecs(sun.calcSunset() * 60);

    bool isDownTime = isWithin(sunrise.hour(), sunrise.minute(), sunset.hour(), sunset.minute());

    if (shutterMode->rawValue().isValid() && shutterMode->rawValue().toInt() == SHUTTER_OPERATION_MODE_AUTO) {
        if (isDownTime) {
            // down: check is presence active
            if (!presenceActive && shutterActor->rawValue().toInt() != SHUTTER_CLOSED) {
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
