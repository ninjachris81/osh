#ifndef ACTORBASEUI_H
#define ACTORBASEUI_H

#include <QObject>
#include "value/valuebaseui.h"

class ActorBaseUI : public ValueBaseUI
{
    Q_OBJECT
public:
    explicit ActorBaseUI(QObject *parent = nullptr);

signals:

public slots:
};

#endif // ACTORBASEUI_H
