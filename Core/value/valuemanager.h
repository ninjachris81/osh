#ifndef VALUEMANAGER_H
#define VALUEMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "valuegroup.h"
#include "valuebase.h"
#include "valuemanagerbase.h"
#include "communication/messagebase.h"

#include <QTimer>
#include <QMap>

class ValueManager : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ValueManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void registerValue(ValueBase* value);

    void updateValue(ValueBase* value, QVariant newValue);
    void updateValue(QString valueGroupId, QString valueId, QVariant newValue);

    void invalidateValue(ValueBase* value);

protected:
    ValueBase* getValue(QString fullId);
    ValueBase* getValue(QString valueGroupId, QString valueId);

    QMap<QString, ValueBase*> m_values;
    QTimer m_valueCheckTimer;

private slots:
    void checkValues();

signals:

public slots:
};

#endif // VALUEMANAGER_H
