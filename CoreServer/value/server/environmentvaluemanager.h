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

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

protected slots:
    void updateValues();

private:
    QTimer m_valueTimer;
    LongValue* m_systemTime;

signals:

public slots:
};

#endif // ENVIRONMENTVALUEMANAGER_H
