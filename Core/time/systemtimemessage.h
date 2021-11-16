#ifndef SYSTEMTIMEMESSAGE_H
#define SYSTEMTIMEMESSAGE_H

#include <QObject>
#include "communication/messagebase.h"

class SystemtimeMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit SystemtimeMessage(qint64 ts, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;


    qlonglong ts();

private:
    qlonglong m_ts;

signals:

public slots:
};

#endif // SYSTEMTIMEMESSAGE_H
