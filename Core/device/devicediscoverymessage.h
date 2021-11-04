#ifndef DEVICEDISCOVERYMESSAGE_H
#define DEVICEDISCOVERYMESSAGE_H

#include <QObject>

#include "communication/messagebase.h"

#include "shared/controllercmdtypes_qt.h"

class DeviceDiscoveryMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit DeviceDiscoveryMessage(QString deviceId, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();


    QString deviceId();

protected:
    QString m_deviceId;

signals:

public slots:
};

#endif // DEVICEDISCOVERYMESSAGE_H
