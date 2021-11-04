#ifndef KNOWNDEVICE_H
#define KNOWNDEVICE_H

#include <QObject>

#include "devicebase.h"

class KnownDevice : public DeviceBase
{
    Q_OBJECT
public:
    explicit KnownDevice(QString id, QString location, QObject *parent = nullptr);

    QString location();

private:
    QString m_location;

signals:

public slots:
};

#endif // KNOWNDEVICE_H
