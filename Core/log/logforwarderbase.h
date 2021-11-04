#ifndef LOGFORWARDERBASE_H
#define LOGFORWARDERBASE_H

#include <QObject>

class LogForwarderBase : public QObject
{
    Q_OBJECT
public:
    explicit LogForwarderBase(QObject *parent = nullptr);

signals:

public slots:
};

#endif // LOGFORWARDERBASE_H
