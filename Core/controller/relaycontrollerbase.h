#ifndef RELAYCONTROLLERBASE_H
#define RELAYCONTROLLERBASE_H

#include <QObject>
#include <QBitArray>
#include <QMap>

#include "controllerbase.h"
#include "controllermessage.h"

#include "actor/digitalactor.h"
#include "value/client/valuemanagerclient.h"

class RelayControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit RelayControllerBase(ControllerManager* manager, QString id, quint8 relayCount, QObject *parent = nullptr);

    virtual void switchStatus(quint8 relayIndex, bool status) = 0;

    void switchStatusAll(bool status);

    /*virtual*/ void handleMessage(ControllerMessage *msg);

    bool relayStatus(quint8 relayIndex);

    void bindActor(DigitalActor *actor, quint8 relayIndex);
    void bindValueManager(ValueManagerClient* clientValueManager);

protected:
    void setStatus(quint8 relayIndex, bool status);

    quint8 m_relayCount = 0;
    QBitArray m_relayStatus;
    QMap<quint8, DigitalActor*> m_actorMappings;

signals:
    void relayStatusChanged(quint8 relayIndex);

public slots:
};

#endif // RELAYCONTROLLERBASE_H
