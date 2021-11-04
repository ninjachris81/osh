#ifndef CLIENTSYSTEMTIMEMANAGER_H
#define CLIENTSYSTEMTIMEMANAGER_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/messagebase.h"

class ClientSystemtimeManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ClientSystemtimeManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

private:
    void setSystemTime(qint64 ts);

signals:

public slots:
};

#endif // CLIENTSYSTEMTIMEMANAGER_H
