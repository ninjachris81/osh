#ifndef VALUEMESSAGE_H
#define VALUEMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"
#include "value/valuebase.h"

class SHARED_LIB_EXPORT ValueMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ValueMessage(QString valueGroupId, QString valueId, QVariant rawValue, QObject *parent = nullptr);
    explicit ValueMessage(QString valueGroupId, QString valueId, QVariantMap value, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;


    QString valueGroupId();
    QString valueId();
    QVariant rawValue();

    QString fullId();

protected:
    QString m_valueGroupId;
    QString m_valueId;
    QVariant m_rawValue;

signals:

public slots:
};

#endif // VALUEMESSAGE_H
