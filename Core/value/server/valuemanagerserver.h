#ifndef VALUEMANAGERSERVER_H
#define VALUEMANAGERSERVER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"

#include <QTimer>
#include <QMap>

class ValueManagerServer : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerServer(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg);

    void updateValue(ValueBase* value, QVariant newValue);
    void updateValue(QString valueGroupId, QString valueId, QVariant newValue);

    void invalidateValue(ValueBase* value);

protected:
    QTimer m_valueCheckTimer;

private slots:
    void checkValues();

signals:

public slots:
};

#endif // VALUEMANAGERSERVER_H
