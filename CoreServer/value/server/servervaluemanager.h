#ifndef SERVERVALUEMANAGER_H
#define SERVERVALUEMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "sharedlib.h"

#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"
#include "database/simpledatabasemanager.h"
#include "communication/communicationmanagerbase.h"

#include <QTimer>
#include <QMap>

class SHARED_LIB_EXPORT ServerValueManager : public ValueManagerBase
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
    SimpleDatabaseManager* m_simpleDatabaseManager = nullptr;

    void valueReceived(ValueBase* value, QVariant newValue);
    void valueReceived(QString valueGroupId, QString valueId, QVariant newValue);

private slots:
    void checkValues();
    void onConnected();

signals:

public slots:
};

#endif // SERVERVALUEMANAGER_H
