#ifndef SYSTEMWARNINGMESSAGE_H
#define SYSTEMWARNINGMESSAGE_H

#include <QObject>

#include "communication/messagebase.h"
#include "device/client/clientdevice.h"

class SystemWarningMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit SystemWarningMessage(QString deviceId, QString msg, QObject *parent = nullptr);
    explicit SystemWarningMessage(ClientDevice* device, QString msg, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString deviceId();
    QString msg();

private:
    QString m_deviceId;
    QString m_msg;

signals:

public slots:
};

#endif // SYSTEMWARNINGMESSAGE_H
