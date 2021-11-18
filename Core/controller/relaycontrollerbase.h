#ifndef RELAYCONTROLLERBASE_H
#define RELAYCONTROLLERBASE_H

#include <QObject>
#include <QList>

#include "controllerbase.h"
#include "controllermessage.h"

#include "actor/digitalactor.h"
#include "value/client/clientvaluemanager.h"

class RelayControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit RelayControllerBase(ControllerManager* manager, QString id, quint8 relayCount, QObject *parent = nullptr);

    virtual void switchStatus(quint8 relayIndex, bool status) = 0;

    void switchStatusAll(bool status);

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    bool relayStatus(quint8 relayIndex);

    /*virtual*/ quint8 bindActor(DigitalActor *actor);

protected:
    void setStatus(quint8 relayIndex, bool status);

    quint8 m_relayCount = 0;
    QList<DigitalActor*> m_actorMappings;

signals:

public slots:
};

#endif // RELAYCONTROLLERBASE_H
