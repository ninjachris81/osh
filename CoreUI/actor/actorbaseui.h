#ifndef ACTORBASEUI_H
#define ACTORBASEUI_H

#include <QObject>
#include "value/valuebaseui.h"

#include "shared/actor_qt.h"


class ActorBaseUI : public ValueBaseUI
{
    Q_OBJECT
public:
    explicit ActorBaseUI(QObject *parent = nullptr);

    Q_INVOKABLE void triggerCmd(actor::ACTOR_CMDS cmd);

signals:

public slots:
};

#endif // ACTORBASEUI_H
