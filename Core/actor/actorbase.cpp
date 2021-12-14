#include "actorbase.h"

#include <QDebug>

ActorBase::ActorBase(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase (valueGroup, id, UT_UNKNOWN, parent)
{

}

void ActorBase::triggerCmd(ACTOR_CMDS cmd) {
    iDebug() << Q_FUNC_INFO << cmd;

    if (cmdSupported(cmd)) {
        _triggerCmd(cmd);
        Q_EMIT(cmdTriggered(cmd));
    } else {
        iWarning() << "Cmd not supported" << cmd;
    }
}

/*
void ActorBase::triggerCmd(int cmd) {
    iDebug() << Q_FUNC_INFO << cmd;
    triggerCmd(static_cast<ACTOR_CMDS>(cmd));
}
*/
