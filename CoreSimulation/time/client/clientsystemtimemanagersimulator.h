#ifndef CLIENTSYSTEMTIMEMANAGERSIMULATOR_H
#define CLIENTSYSTEMTIMEMANAGERSIMULATOR_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "time/client/clientsystemtimemanager.h"

class ClientSystemtimeManagerSimulator : public ClientSystemtimeManager
{
    Q_OBJECT
public:
    explicit ClientSystemtimeManagerSimulator(QObject *parent = nullptr);

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

#endif // CLIENTSYSTEMTIMEMANAGERSIMULATOR_H
