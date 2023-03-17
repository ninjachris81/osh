#include "aplayprocesswrapper.h"

APlayProcessWrapper::APlayProcessWrapper(QString cmd, AudioPlaybackActor *actor, QObject *parent)
    : AudioProcessWrapperBase{actor->audioDeviceIds().at(0), parent}
{
    setProgram(cmd);
    QStringList args;
    args << "-D" << actor->audioDeviceIds().at(0);


}
