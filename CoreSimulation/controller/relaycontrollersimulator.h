#ifndef RELAYCONTROLLERSIMULATOR_H
#define RELAYCONTROLLERSIMULATOR_H

#include <QObject>
#include <QList>

#include "controller/relaycontrollerbase.h"
#include "controller/controllermessage.h"

#include "actor/digitalactor.h"
#include "value/client/clientvaluemanager.h"

class RelayControllerSimulator : public RelayControllerBase
{
    Q_OBJECT
public:
    explicit RelayControllerSimulator(ControllerManager* manager, QString id, quint8 relayCount, QObject *parent = nullptr);

    /*virtual*/ void switchStatus(quint8 relayIndex, bool status);

protected:

signals:

public slots:
};

#endif // RELAYCONTROLLERSIMULATOR_H
