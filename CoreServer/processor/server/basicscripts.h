#pragma once

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
    explicit BasicScripts(DatamodelBase* datamodel, LocalStorage* localStorage, TaskStorage* taskStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);


    Q_INVOKABLE bool initConnectValues(QString valueSourceIds, QString valueTargetId);

    Q_INVOKABLE bool initTriggerCmdOnValue(QString valueSourceIds, QVariant triggerValue, QString actorId, int actorCmd, int retriggerTimeout = 0);

    Q_INVOKABLE bool initMapCmd(QString sourceActorId, QString triggerActorId, int sourceCmd, int triggerCmd);

    Q_INVOKABLE bool initFollowActor(QString actorSourceId, QString triggerActorId, int followMode);

    Q_INVOKABLE bool startTimer(QString timerActorId);

    Q_INVOKABLE bool stopTimer(QString timerActorId);

    Q_INVOKABLE bool initTurnOnWhileTimerActive(QString timerActorId, QString actorId);

private slots:
    void initConnectValues_valueChanged();
    void initMapCmd_cmdTriggered(ACTOR_CMDS cmd);
    void initTriggerCmdOnValue_valueChanged();
    void initFollowActor_cmdTriggered(ACTOR_CMDS cmd);
    void initFollowActor_valueChanged();
    void initTurnOnWhileTimerActive_timerCmdTriggered(ACTOR_CMDS cmd);
    void initTurnOnWhileTimerActive_valueChanged();

private:
    QList<ActorBase*> m_ignoreFollowActors;

signals:

};

