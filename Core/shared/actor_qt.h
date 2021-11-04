#ifndef ACTOR_QT_H
#define ACTOR_QT_H

#define USES_ACTOR_QT

#include "actor.h"
#include "constants.h"

#include <QObject>
#include <QVariant>

enum ACTOR_CMDS {
    ACTOR_CMD_UNKNOWN = ENUM_UNKNOWN,
    ACTOR_CMD_ON = ACTOR_ON,
    ACTOR_CMD_OFF = ACTOR_OFF,
    ACTOR_CMD_UP = ACTOR_UP,
    ACTOR_CMD_DOWN = ACTOR_DOWN
};


#endif // ACTOR_QT_H
