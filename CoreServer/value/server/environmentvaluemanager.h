#ifndef ENVIRONMENTVALUEMANAGER_H
#define ENVIRONMENTVALUEMANAGER_H

#include <QObject>
#include <QTimer>

#include "manager/managerbase.h"
#include "value/longvalue.h"

class EnvironmentValueManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit EnvironmentValueManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

protected slots:
    void updateValues();

private:
    QTimer m_valueTimer;
    LongValue* m_systemTime;

signals:

public slots:
};

#endif // ENVIRONMENTVALUEMANAGER_H
