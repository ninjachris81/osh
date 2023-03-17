#ifndef AUDIOPROCESSWRAPPERBASE_H
#define AUDIOPROCESSWRAPPERBASE_H

#include <QProcess>


class AudioProcessWrapperBase : public QProcess {
    Q_OBJECT

public:
    AudioProcessWrapperBase(QObject *parent = nullptr);

};

#endif // AUDIOPROCESSWRAPPERBASE_H
