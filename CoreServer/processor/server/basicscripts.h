#ifndef BASICSCRIPTS_H
#define BASICSCRIPTS_H

#include <QObject>
#include "processor/server/scriptbase.h"
#include "value/valuebase.h"
#include "actor/actorbase.h"
#include "datamodel/datamodelbase.h"
#include "processor/server/localstorage.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

class BasicScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit BasicScripts(DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);


    Q_INVOKABLE bool initConnectValues(QString valueSourceIds, QString valueTargetId);

    Q_INVOKABLE bool initTriggerCmdOnValue(QString valueSourceIds, QVariant triggerValue, QString actorId, int actorCmd);

private slots:
    void initConnectValues_valueChanged();
    void initTriggerCmdOnValue_valueChanged();

signals:

};

#endif // BASICSCRIPTS_H
