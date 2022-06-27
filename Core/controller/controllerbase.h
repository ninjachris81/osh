#ifndef CONTROLLERBASE_H
#define CONTROLLERBASE_H

#include <QObject>

#include "identifyable.h"
#include "config/localconfig.h"
#include "value/client/clientvaluemanager.h"
#include "actor/actorbase.h"
#include "shared/controllercmdtypes_qt.h"

#include "macros.h"

class ControllerManager;    // fwddcl
class ControllerMessage;    // fwddcl

class ControllerBase : public Identifyable
{
    Q_OBJECT
public:
    enum CONTROLLER_CMD_TYPE {
        CCT_UNKNOWN = ENUM_UNKNOWN,
        CCT_ENABLE = CONTROLLER_CMD_TYPE_ENABLE,
    };
    Q_ENUM(CONTROLLER_CMD_TYPE)

    explicit ControllerBase(ControllerManager* manager, QString id, QObject *parent = nullptr);

    void setConfig(LocalConfig* config);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    virtual void init() = 0;

    virtual void start() = 0;

    virtual void handleMessage(ControllerMessage *msg) = 0;

    virtual quint8 bindActor(ActorBase *actor) { Q_UNUSED(actor) return 0; }
    virtual quint8 bindValue(ValueBase *value) { Q_UNUSED(value) return 0; }
    virtual void bindValueManager(ClientValueManager* clientValueManager, QList<ValueBase*> valueOrActors);

protected:
    ControllerManager *m_manager;
    LocalConfig* m_config;

signals:
    void controllerConnected();
    void controllerDisconnected();

public slots:
};

#endif // CONTROLLERBASE_H
