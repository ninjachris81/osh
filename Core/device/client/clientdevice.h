#ifndef CLIENTDEVICE_H
#define CLIENTDEVICE_H

#include <QObject>
#include "device/devicebase.h"

class ClientDevice : public DeviceBase
{
    Q_OBJECT
public:
    explicit ClientDevice(QString id, QString serviceId, QObject *parent = nullptr);

signals:

public slots:
};

#endif // CLIENTDEVICE_H
