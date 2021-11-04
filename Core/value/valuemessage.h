#ifndef VALUEMESSAGE_H
#define VALUEMESSAGE_H

#include <QObject>

#include "communication/messagebase.h"
#include "value/valuebase.h"

class ValueMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ValueMessage(QString valueGroupId, QString valueId, QVariant rawValue, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();


    QString valueGroupId();
    QString valueId();
    QVariant rawValue();

protected:
    QString m_valueGroupId;
    QString m_valueId;
    QVariant m_rawValue;

signals:

public slots:
};

#endif // VALUEMESSAGE_H
