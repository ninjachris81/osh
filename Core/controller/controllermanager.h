#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QMap>

#include "controller/controllerbase.h"
#include "manager/managerbase.h"
#include "communication/messagebase.h"

class ControllerManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ControllerManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ void postInit();

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

    void registerController(ControllerBase *controller);

    ControllerBase* getController(QString id);

    QStringList controllerNames();

private:
    QMap<QString, ControllerBase*> m_controllers;

signals:

public slots:
};

#endif // CONTROLLERMANAGER_H
