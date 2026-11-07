#pragma once

#include <QObject>

#include "sharedlib.h"

#include "actorbase.h"

class SHARED_LIB_EXPORT TimerActor : public ActorBase
{
    Q_OBJECT
public:
    explicit TimerActor();
    TimerActor(ValueGroup *valueGroup, QString id, VALUE_TYPE valueType, QObject *parent = nullptr);

    bool cmdSupported(ACTOR_CMDS cmd) override;

    QVariant _updateValue(QVariant newValue) override;

    bool isAsync() override;

    bool isRunning();

    void updateTimeLeft();

private:
    void startTimer();
    void stopTimer();

    quint64 calculateMsLeft();

protected:
    quint64 m_startTime = 0;
    bool m_isRunning = false;
    void _triggerCmd(ACTOR_CMDS cmd) override;

};

