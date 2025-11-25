#ifndef ADVANCEDSCRIPTS_H
#define ADVANCEDSCRIPTS_H

#include <QObject>

#include "processor/server/scriptbase.h"
#include "value/valuebase.h"

#define SHUTTER_TILT_MODE_NORMAL 0           // normal open
#define SHUTTER_TILT_MODE_TILT   1           // tilt due to heat
#define SHUTTER_TILT_MODE_CLOSE  2           // close due to extreme heat

class AdvancedScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit AdvancedScripts(DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    Q_INVOKABLE bool applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, double lat, double lng, int timezone, int adjustmentSunrise, int adjustmentSunset, QString tiltThresholdTempFullId, double tiltThresholdTemperature, double closeThresholdTemperature, QString reportTiltModeFullId, QString windowOpenFullId);

signals:

};

#endif // ADVANCEDSCRIPTS_H
