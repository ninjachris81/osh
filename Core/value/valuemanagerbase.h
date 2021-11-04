#ifndef VALUEMANAGERBASE_H
#define VALUEMANAGERBASE_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "valuebase.h"

class ValueManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit ValueManagerBase(QObject *parent = nullptr);

    void publishValue(ValueBase* value);

signals:

public slots:
};

#endif // VALUEMANAGERBASE_H
