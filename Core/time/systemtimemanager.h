#ifndef SYSTEMTIMEMANAGER_H
#define SYSTEMTIMEMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"

class SystemtimeManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit SystemtimeManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

private slots:
    void sendSystemtime();

private:
    QTimer m_bcTimer;
    CommunicationManagerBase* m_commManager;

signals:

public slots:
};

#endif // SYSTEMTIMEMANAGER_H
