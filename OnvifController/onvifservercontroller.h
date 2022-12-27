#ifndef ONVIFSERVERCONTROLLER_H
#define ONVIFSERVERCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "controller/controllermessage.h"

#include "onvifserverthread.h"

class SHARED_LIB_EXPORT OnvifServerController : public ControllerBase
{
    Q_OBJECT
public:
    explicit OnvifServerController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    /*virtual*/ quint8 bindValue(ValueBase* value) override;

private:
    OnvifServerThread* m_onvifServerThread;

signals:

};

#endif // ONVIFSERVERCONTROLLER_H
