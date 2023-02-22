#ifndef KNOWNDEVICE_H
#define KNOWNDEVICE_H

#include <QObject>

#include "sharedlib.h"

#include "device/devicebase.h"
#include "datamodel/serializationsupport.h"

class SHARED_LIB_EXPORT KnownDevice : public DeviceBase
{
    Q_OBJECT
public:
    static QLatin1String PROPERTY_SERVICE_ID;
    static QLatin1String PROPERTY_NAME;

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
