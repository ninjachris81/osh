#ifndef CONTROLLERBASE_H
#define CONTROLLERBASE_H

#include <QObject>

#include "identifyable.h"
#include "config/localconfig.h"
#include "controllermessage.h"

class ControllerManager;    // fwddcl

class ControllerBase : public Identifyable
{
    Q_OBJECT
public:
    explicit ControllerBase(ControllerManager* manager, QString id, QObject *parent = nullptr);

    void setConfig(LocalConfig* config);

    virtual void init() = 0;

    virtual void handleMessage(ControllerMessage *msg) = 0;

protected:
    ControllerManager *m_manager;
    LocalConfig* m_config;

signals:
    void controllerConnected();
    void controllerDisconnected();

public slots:
};

#endif // CONTROLLERBASE_H
