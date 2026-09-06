#pragma once

#include <QObject>
#include "value/valuebaseui.h"

#include "shared/actor_qt.h"
#include "actor/actorbase.h"

class ActorBaseUI : public ValueBaseUI
{
    Q_OBJECT
public:
    explicit ActorBaseUI(Identifyable *parent = nullptr);

    ActorBase* parent();

    Q_INVOKABLE void triggerCmd(ACTOR_CMDS cmd, QString reason);

private:
    ActorBase* m_actor;

signals:

public slots:
};

