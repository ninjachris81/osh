#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QList>

#include "manager/managerbase.h"
#include "communication/messagebase.h"

class LogManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit LogManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

signals:

public slots:
};

#endif // LOGMANAGER_H
