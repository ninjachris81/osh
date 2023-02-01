#ifndef DIGITALINPUTCONTROLLERBASE_H
#define DIGITALINPUTCONTROLLERBASE_H

#include <QObject>
#include <QBitArray>
#include <QList>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "value/booleanvalue.h"

class SHARED_LIB_EXPORT DigitalInputControllerBase : public ControllerBase
{
    Q_OBJECT
public:
    explicit DigitalInputControllerBase(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    /*virtual*/ quint8 bindValue(BooleanValue *value);

    virtual quint8 inputCount() = 0;

    bool inputStatus(quint8 valueIndex);

protected:
    QBitArray m_inputStatus;
    QList<BooleanValue*> m_valueMappings;

signals:

public slots:
};

#endif // DIGITALINPUTCONTROLLERBASE_H
