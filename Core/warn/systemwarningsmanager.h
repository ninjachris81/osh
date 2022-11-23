#ifndef SYSTEMWARNINGSMANAGER_H
#define SYSTEMWARNINGSMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"

class SHARED_LIB_EXPORT SystemWarningsManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit SystemWarningsManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

signals:

public slots:
};

#endif // SYSTEMWARNINGSMANAGER_H
