#ifndef VALUEMANAGERBASE_H
#define VALUEMANAGERBASE_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "valuebase.h"
#include "valuemessage.h"

class ValueManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerBase(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    virtual void handleReceivedMessage(ValueMessage* msg) = 0;

    void publishValue(ValueBase* value);

    void registerValue(ValueBase* value);

protected:
    ValueBase* getValue(QString fullId);
    ValueBase* getValue(QString valueGroupId, QString valueId);

    QMap<QString, ValueBase*> m_values;

signals:

public slots:
};

#endif // VALUEMANAGERBASE_H
