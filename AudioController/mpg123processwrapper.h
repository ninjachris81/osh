#pragma once

#include "actor/audioplaybackactor.h"
#include "audioprocesswrapperbase.h"

#include <QObject>
#include <QProcess>

class SHARED_LIB_EXPORT MPG123ProcessWrapper : public AudioProcessWrapperBase
{
    Q_OBJECT
public:
    explicit MPG123ProcessWrapper(QString cmd, AudioPlaybackActor* actor, QObject *parent = nullptr);

private:

signals:

};

