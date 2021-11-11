#include "actorbase.h"

#include <QDebug>

ActorBase::ActorBase(ValueGroup *valueGroup, QString id, QObject *parent) : ValueBase (valueGroup, id, parent)
{

}

void ActorBase::triggerCmd(ACTOR_CMDS cmd) {
    qDebug() << Q_FUNC_INFO << cmd;

    if (cmdSupported(cmd)) {
        _triggerCmd(cmd);
    } else {
        qWarning() << "Cmd not supported" << cmd;
    }
}
