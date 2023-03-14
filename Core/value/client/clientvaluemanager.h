#ifndef CLIENTVALUEMANAGER_H
#define CLIENTVALUEMANAGER_H

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"

class SHARED_LIB_EXPORT ClientValueManager : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ClientValueManager(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg) override;

    void registerValue(ValueBase* value) override;

    void registerForMaintenance(ValueBase* value);

private:
    QMap<QString, ValueBase*> m_maintenanceValues;
    QTimer m_maintenanceTimer;

private slots:
    void maintainValues();

    void _onValueChanged();

signals:

public slots:
};

#endif // CLIENTVALUEMANAGER_H
