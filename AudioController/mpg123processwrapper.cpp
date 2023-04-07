#include "mpg123processwrapper.h"

MPG123ProcessWrapper::MPG123ProcessWrapper(QString cmd, AudioPlaybackActor *actor, QObject *parent)
    : AudioProcessWrapperBase{actor, parent}
{
    setProgram(cmd);
    QStringList args;
    args << "-a" << actor->audioDeviceIds().at(0);

    QString file = actor->audioUrl();
    if (file.endsWith(".m3u")) {
        args << "--list" << file;
        args << "--random";
    } else {
        args << file;
    }

    setArguments(args);

    this->setReadChannel(QProcess::StandardOutput);

    connect(this, &QProcess::readyRead, this,[this](){
        QString line = readLine();

        if (line.startsWith("ICY-META: StreamTitle='") && line.contains("';")) {
            line = line.mid(23, line.indexOf("';"));
            Q_EMIT(currentTitleChanged(line));
        }
    });
}
