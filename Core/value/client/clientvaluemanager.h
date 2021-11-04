#ifndef CLIENTVALUEMANAGER_H
#define CLIENTVALUEMANAGER_H

#include <QObject>
#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"

class ClientValueManager : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ClientValueManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);



signals:

public slots:
};

#endif // CLIENTVALUEMANAGER_H
