#ifndef SYSTEMTIMEMESSAGE_H
#define SYSTEMTIMEMESSAGE_H

#include <QObject>
#include "communication/messagebase.h"

class SystemtimeMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit SystemtimeMessage(qint64 ts, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();


    qlonglong ts();

private:
    qlonglong m_ts;

signals:

public slots:
};

#endif // SYSTEMTIMEMESSAGE_H
