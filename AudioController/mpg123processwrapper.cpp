#include "mpg123processwrapper.h"

MPG123ProcessWrapper::MPG123ProcessWrapper(QString cmd, AudioPlaybackActor *actor, QObject *parent)
    : AudioProcessWrapperBase{actor, parent}
{
    setProgram(cmd);
    QStringList args;
    args << "-a" << actor->audioDeviceIds().at(0);

    QString file = actor->rawValue().toString();
    if (file.endsWith(".m3u")) {
        args << "--list" << file;
    } else {
        args << file;
    }
}
