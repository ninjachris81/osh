#ifndef DEVICEDISCOVERYMESSAGE_H
#define DEVICEDISCOVERYMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"

#include "shared/controllercmdtypes_qt.h"

class SHARED_LIB_EXPORT DeviceDiscoveryMessage : public MessageBase
{
    Q_OBJECT
public:
    enum DeviceHealthState {
        Unknown = 0,
        Healthy,
        HasWarnings,
        HasErrors,
    };

    explicit DeviceDiscoveryMessage(QString deviceId, QString serviceId, quint64 upTime, DeviceHealthState healthState, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString fullId();

    QString deviceId();

    QString serviceId();

    quint64 upTime();

    DeviceHealthState healthState();

protected:
    QString m_deviceId;
    QString m_serviceId;
    quint64 m_upTime;
    DeviceHealthState m_healthState = Unknown;

signals:

public slots:
};

#endif // DEVICEDISCOVERYMESSAGE_H
