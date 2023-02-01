#ifndef ACTOR_QT_H
#define ACTOR_QT_H

#define USES_ACTOR_QT

#include "actor.h"
#include "constants.h"

#include "sharedlib.h"

#include <QObject>
#include <QVariant>

namespace actor {
Q_DECL_EXPORT Q_NAMESPACE

    enum ACTOR_CMDS {
        ACTOR_CMD_UNKNOWN = ENUM_UNKNOWN,
        ACTOR_CMD_ON = ACTOR_ON,
        ACTOR_CMD_OFF = ACTOR_OFF,
        ACTOR_CMD_UP = ACTOR_UP,
        ACTOR_CMD_DOWN = ACTOR_DOWN,
        ACTOR_CMD_START = ACTOR_START,
        ACTOR_CMD_STOP = ACTOR_STOP,
        ACTOR_CMD_PAUSE = ACTOR_PAUSE
    };

    Q_ENUM_NS(ACTOR_CMDS);
}


#endif // ACTOR_QT_H
