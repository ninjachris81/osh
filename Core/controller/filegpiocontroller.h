#ifndef FILEGPIOCONTROLLER_H
#define FILEGPIOCONTROLLER_H

#include <QObject>
#include "sharedlib.h"

#include "controller/controllerbase.h"

class SHARED_LIB_EXPORT FileGPIOController : public ControllerBase
{
    Q_OBJECT
public:
    explicit FileGPIOController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init();

    /*virtual*/ void start();

    /*virtual*/ void handleMessage(ControllerMessage *msg);


signals:

public slots:
};

#endif // FILEGPIOCONTROLLER_H
