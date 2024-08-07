#ifndef SYSTEMTIMEMANAGER_H
#define SYSTEMTIMEMANAGER_H

#ifndef IS_OSH_CORE_SERVICE
    #error Should use client version
#endif

#include <QObject>
#include <QTimer>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"

class SHARED_LIB_EXPORT SystemtimeManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit SystemtimeManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

protected:
    virtual qint64 _getSystemTime();

private slots:
    void sendSystemtime();

private:
    QTimer m_bcTimer;
    CommunicationManagerBase* m_commManager;

signals:

public slots:
};

#endif // SYSTEMTIMEMANAGER_H
