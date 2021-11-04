#ifndef CLIENTDEVICEMANAGER_H
#define CLIENTDEVICEMANAGER_H

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "device/client/clientdevice.h"
#include "communication/communicationmanagerbase.h"

class ClientDeviceManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientDeviceManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    QString getName();

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    ClientDevice *device();

private:
    QTimer m_ddTimer;
    ClientDevice* m_device;
    CommunicationManagerBase* m_commManager;

private slots:
    void startDDBroadcast();
    void stopDDBroadcast();
    void sendDDBroadcast();

signals:

public slots:
};

#endif // CLIENTDEVICEMANAGER_H
