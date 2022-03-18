#ifndef DEVICEBASE_H
#define DEVICEBASE_H

#include <QObject>

#include "serializableidentifyable.h"
#include "shared/controllercmdtypes_qt.h"
#include "datamodel/serializationsupport.h"

class DeviceBase : public SerializableIdentifyable
{
    Q_OBJECT
public:
    DeviceBase();
    explicit DeviceBase(QString id, QString serviceId, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    QString fullId();

    QString serviceId();

    void updatePing();

    void updateOnline(qint64 onlineTimeout);

    qint64 lastPing();

    bool isOnline();

protected:
    QString m_serviceId;

private:
    bool m_isOnline = false;
    qint64 m_lastPing = 0;

signals:
    void lastPingChanged();
    void isOnlineChanged();

public slots:
};

#endif // DEVICEBASE_H
