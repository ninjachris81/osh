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

    static QLatin1String MANAGER_ID;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void enableSetTime(bool enable);

private:
    void setSystemTime(qint64 ts);
    bool m_enableSetTime = true;

signals:

public slots:
};

#endif // CLIENTSYSTEMTIMEMANAGER_H
