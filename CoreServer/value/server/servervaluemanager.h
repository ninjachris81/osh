#ifndef SERVERVALUEMANAGER_H
#define SERVERVALUEMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"
#include "database/databasemanager.h"
#include "communication/communicationmanagerbase.h"

#include <QTimer>
#include <QMap>

class ServerValueManager : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ServerValueManager(QObject *parent = nullptr);

    static QLatin1String VALUE_PREFIX;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg);

    void invalidateValue(ValueBase* value);

protected:
    QTimer m_valueCheckTimer;
    CommunicationManagerBase* m_commManager = nullptr;
    DatabaseManager* m_databaseManager = nullptr;

    void valueReceived(ValueBase* value, QVariant newValue);
    void valueReceived(QString valueGroupId, QString valueId, QVariant newValue);

private slots:
    void checkValues();

signals:

public slots:
};

#endif // SERVERVALUEMANAGER_H
