#ifndef KNOWNDEVICE_H
#define KNOWNDEVICE_H

#include <QObject>

#include "device/devicebase.h"
#include "datamodel/serializationsupport.h"

class KnownDevice : public DeviceBase
{
    Q_OBJECT
public:
    explicit KnownDevice();
    explicit KnownDevice(QString id, QString serviceId, QString name, QObject *parent = nullptr);

    QString name();

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

protected:
    QString m_name;

signals:

public slots:
};

#endif // KNOWNDEVICE_H
