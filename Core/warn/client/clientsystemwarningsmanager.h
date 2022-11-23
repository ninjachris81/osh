#ifndef CLIENTSYSTEMWARNINGSMANAGER_H
#define CLIENTSYSTEMWARNINGSMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "device/client/clientdevicemanager.h"

class SHARED_LIB_EXPORT ClientSystemWarningsManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientSystemWarningsManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void raiseWarning(QString msg);

private:
    CommunicationManagerBase* m_commManager = nullptr;
    ClientDeviceDiscoveryManager* m_clientDeviceManager = nullptr;

signals:

public slots:
};

#endif // CLIENTSYSTEMWARNINGSMANAGER_H
