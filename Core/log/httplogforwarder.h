#ifndef HTTPLOGFORWARDER_H
#define HTTPLOGFORWARDER_H

#include <QObject>
#include "logforwarderbase.h"

class HttpLogforwarder : public LogForwarderBase
{
    Q_OBJECT
public:
    explicit HttpLogforwarder(QObject *parent = nullptr);

signals:

public slots:
};

#endif // HTTPLOGFORWARDER_H
