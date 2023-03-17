#ifndef AUDIOPROCESSWRAPPERBASE_H
#define AUDIOPROCESSWRAPPERBASE_H

#include "actor/audioplaybackactor.h"
#include <QProcess>


class AudioProcessWrapperBase : public QProcess {
    Q_OBJECT

public:
    AudioProcessWrapperBase(AudioPlaybackActor *audioActor, QObject *parent = nullptr);

    AudioPlaybackActor *audioActor();

private:
    AudioPlaybackActor *m_audioActor;

};

#endif // AUDIOPROCESSWRAPPERBASE_H
