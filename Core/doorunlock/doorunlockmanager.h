#ifndef DOORUNLOCKMANAGER_H
#define DOORUNLOCKMANAGER_H

#include <QObject>
#include <QMap>
#include <QMutex>
#include <QTimer>

#include "actor/actormanager.h"
#include "sharedlib.h"

#include "manager/managerbase.h"
#include "communication/communicationmanagerbase.h"
#include "user/usermanager.h"
#include "doorunlock/doorunlockmessage.h"

#ifdef QT_DEBUG
    #define DU_CHALLENGE_TIMEOUT_MS 120000
#else
    #define DU_CHALLENGE_TIMEOUT_MS 1000
#endif

class SHARED_LIB_EXPORT DoorUnlockManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DoorUnlockManager(QObject *parent = nullptr);

    struct ChallengeRequest {
        qint64 ts;
        QString oth;
    };

    static QLatin1String MANAGER_ID;

    static QLatin1String PSK;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ QString id() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

private slots:
    void onChallengeMaintenance();

private:
    CommunicationManagerBase* m_commManager;
    ActorManager *m_actorManager;
    UserManager* m_userManager;

    QMutex m_currentChallengeRequestsMutex;
    QTimer m_currentChallengeRequestsTimer;

    QMap<QString, ChallengeRequest> m_currentChallengeRequests;

    void handleChallengeRequest(DoorUnlockMessage* duMessage);

    void handleChallengeCalculated(DoorUnlockMessage* duMessage);

    void sendResult(QString userId, QString doorId, bool success);

    QString calculateResultHash(qint64 ts, QString oth, QString userId, QString doorId);

signals:
    void unlockDoor(QString doorId);

};

#endif // DOORUNLOCKMANAGER_H
