#ifndef DEVICEDISCOVERYMESSAGE_H
#define DEVICEDISCOVERYMESSAGE_H

#include <QObject>

#include "communication/messagebase.h"

#include "shared/controllercmdtypes_qt.h"

class DeviceDiscoveryMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryMessage(QString deviceId, QString serviceId, quint64 upTime, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString fullId();

    QString deviceId();

    QString serviceId();

    quint64 upTime();

protected:
    QString m_deviceId;
    QString m_serviceId;
    quint64 m_upTime;

signals:

public slots:
};

#endif // DEVICEDISCOVERYMESSAGE_H
