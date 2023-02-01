#ifndef DIGITALINPUTCONTROLLERSIMULATOR_H
#define DIGITALINPUTCONTROLLERSIMULATOR_H

#include <QObject>
#include <QBitArray>
#include <QList>

#include "sharedlib.h"

#include "controller/digitalinputcontrollerbase.h"

class SHARED_LIB_EXPORT DigitalInputControllerSimulator : public DigitalInputControllerBase
{
    Q_OBJECT
public:
    explicit DigitalInputControllerSimulator(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ quint8 inputCount() override;

    void setStatus(quint8 valueIndex, bool value);

signals:

public slots:
};

#endif // DIGITALINPUTCONTROLLERSIMULATOR_H
