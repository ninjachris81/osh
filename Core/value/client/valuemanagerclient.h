#ifndef CLIENTVALUEMANAGER_H
#define CLIENTVALUEMANAGER_H

#include <QObject>
#include "value/valuemanagerbase.h"
#include "communication/messagebase.h"

class ValueManagerClient : public ValueManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerClient(QObject *parent = nullptr);

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void handleReceivedMessage(ValueMessage* msg);

signals:

public slots:
};

#endif // CLIENTVALUEMANAGER_H
