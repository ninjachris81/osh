#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QMap>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "manager/managerbase.h"
#include "communication/messagebase.h"

class SHARED_LIB_EXPORT ControllerManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit ControllerManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ void postInit() override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void registerController(ControllerBase *controller);

    ControllerBase* getController(QString id);

    QStringList controllerNames();

private:
    QMap<QString, ControllerBase*> m_controllers;

private slots:
    void onStart();

signals:

public slots:
};

#endif // CONTROLLERMANAGER_H
