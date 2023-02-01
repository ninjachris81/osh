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

private:
    QTimer m_maintenanceTimer;

private slots:
    void maintainValues();

signals:

public slots:
};

#endif // CLIENTVALUEMANAGER_H
