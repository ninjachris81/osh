#ifndef APLAYPROCESSWRAPPER_H
#define APLAYPROCESSWRAPPER_H

#include "actor/audioplaybackactor.h"
#include "audioprocesswrapperbase.h"

#include <QObject>
#include <QProcess>

class SHARED_LIB_EXPORT APlayProcessWrapper : public AudioProcessWrapperBase
{
    Q_OBJECT
public:
    explicit APlayProcessWrapper(QString cmd, AudioPlaybackActor* actor, QObject *parent = nullptr);

signals:

};

#endif // APLAYPROCESSWRAPPER_H
