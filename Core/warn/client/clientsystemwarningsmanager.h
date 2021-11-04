#ifndef CLIENTSYSTEMWARNINGSMANAGER_H
#define CLIENTSYSTEMWARNINGSMANAGER_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "device/client/clientdevicemanager.h"

class ClientSystemWarningsManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientSystemWarningsManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void raiseWarning(QString msg);

private:
    CommunicationManagerBase* m_commManager = nullptr;
    ClientDeviceManager* m_clientDeviceManager = nullptr;

signals:

public slots:
};

#endif // CLIENTSYSTEMWARNINGSMANAGER_H
