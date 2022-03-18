#ifndef ACTORBASEUI_H
#define ACTORBASEUI_H

#include <QObject>
#include "value/valuebaseui.h"

#include "shared/actor_qt.h"
#include "actor/actorbase.h"

class ActorBaseUI : public ValueBaseUI
{
    Q_OBJECT
public:
    explicit ActorBaseUI(QObject *parent = nullptr);

    ActorBase* parent();

    Q_INVOKABLE void triggerCmd(actor::ACTOR_CMDS cmd, QString reason);

private:
    ActorBase* m_actor;

signals:

public slots:
};

#endif // ACTORBASEUI_H
