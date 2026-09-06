#pragma once

#include <QObject>

#include "sharedlib.h"

#include "device/devicebase.h"

class SHARED_LIB_EXPORT ClientDevice : public DeviceBase
{
    Q_OBJECT
public:
    explicit ClientDevice(QString id, QString serviceId, QObject *parent = nullptr);

signals:

public slots:
};

