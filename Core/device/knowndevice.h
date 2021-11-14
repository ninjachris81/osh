#ifndef KNOWNDEVICE_H
#define KNOWNDEVICE_H

#include <QObject>

#include "device/devicebase.h"

class KnownDevice : public DeviceBase
{
    Q_OBJECT
public:
    explicit KnownDevice(QString id, QString name, QObject *parent = nullptr);

    QString name();

protected:
    QString m_name;

signals:

public slots:
};

#endif // KNOWNDEVICE_H
