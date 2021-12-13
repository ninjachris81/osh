#ifndef SIMULATORBASE_H
#define SIMULATORBASE_H

#include <QObject>
#include "identifyable.h"

class SimulatorBase : public Identifyable
{
    Q_OBJECT
public:
    explicit SimulatorBase(QString id, QObject *parent = nullptr);

signals:

};

#endif // SIMULATORBASE_H
