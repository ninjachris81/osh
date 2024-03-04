#ifndef ADVANCEDSCRIPTS_H
#define ADVANCEDSCRIPTS_H

#include <QObject>

#include "processor/server/scriptbase.h"
#include "value/valuebase.h"

class AdvancedScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit AdvancedScripts(DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    Q_INVOKABLE bool applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, double lat, double lng, int timezone, int adjustmentSunrise, int adjustmentSunset);

signals:

};

#endif // ADVANCEDSCRIPTS_H
