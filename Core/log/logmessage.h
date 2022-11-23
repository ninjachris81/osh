#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"

class SHARED_LIB_EXPORT LogMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit LogMessage(QString deviceId, QtMsgType logType, QString message, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString deviceId();
    QtMsgType logType();
    QString message();

private:
    QString m_deviceId;
    QtMsgType m_logType;
    QString m_message;

signals:

public slots:
};

#endif // LOGMESSAGE_H
