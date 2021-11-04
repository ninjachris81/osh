#ifndef SYSTEMWARNINGSMANAGER_H
#define SYSTEMWARNINGSMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "manager/managerbase.h"

class SystemWarningsManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit SystemWarningsManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

signals:

public slots:
};

#endif // SYSTEMWARNINGSMANAGER_H
