#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <QObject>
#include "communication/messagebase.h"

class LogMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit LogMessage(QString deviceId, QString message, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString deviceId();
    QString message();

private:
    QString m_deviceId;
    QString m_message;

signals:

public slots:
};

#endif // LOGMESSAGE_H
