#ifndef RELAYCONTROLLERBASE_H
#define RELAYCONTROLLERBASE_H

#include <QObject>
#include <QBitArray>

#include "controllerbase.h"
#include "controllermessage.h"

class RelayControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit RelayControllerBase(ControllerManager* manager, QString id, quint8 relayCount, QObject *parent = nullptr);

    virtual void switchStatus(quint8, bool status) = 0;

    /*virtual*/ void handleMessage(ControllerMessage *msg);

protected:
    void setStatus(quint8 relayIndex, bool status);

    quint8 m_relayCount = 0;
    QBitArray m_relayStatus;

signals:
    void relayStatusChanged(quint8 relayIndex);

public slots:
};

#endif // RELAYCONTROLLERBASE_H
