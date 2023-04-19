#include "doorunlockmanager.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <QCryptographicHash>

#include "actor/dooractor.h"
#include "macros.h"
#include "user/oshuser.h"

QLatin1String DoorUnlockManager::MANAGER_ID = QLatin1String("DoorUnlockManager");

DoorUnlockManager::DoorUnlockManager(QObject *parent) : ManagerBase(parent)
{
    connect(&m_currentChallengeRequestsTimer, &QTimer::timeout, this, &DoorUnlockManager::onChallengeMaintenance);
    m_currentChallengeRequestsTimer.setInterval(1000);
}

LogCat::LOGCAT DoorUnlockManager::logCat() {
    return LogCat::DOOR_UNLOCK;
}

QString DoorUnlockManager::id() {
    return MANAGER_ID;
}

void DoorUnlockManager::init(LocalConfig *config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);
    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    REQUIRE_MANAGER(UserManager);
    m_userManager = getManager<UserManager>(UserManager::MANAGER_ID);

    REQUIRE_MANAGER(ActorManager);
    m_actorManager = getManager<ActorManager>(ActorManager::MANAGER_ID);

    //m_currentChallengeRequestsTimer.start();
}

MessageBase::MESSAGE_TYPE DoorUnlockManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DOOR_UNLOCK;
}

void DoorUnlockManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    DoorUnlockMessage* duMessage = static_cast<DoorUnlockMessage*>(msg);

    // first, check if user is allowed
    OshUser* user = m_userManager->user(duMessage->userId());
    DoorActor *door = static_cast<DoorActor*>(m_actorManager->getActor(duMessage->doorId()));

    if (user != nullptr && door != nullptr) {
        if (user->rights().contains(OshUser::USER_RIGHT_UNLOCK_DOOR)) {
            if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_STAGE)) {
                DoorUnlockMessage::DU_AUTH_STAGE stage = static_cast<DoorUnlockMessage::DU_AUTH_STAGE>(duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_STAGE).toUInt());

                switch(stage) {
                case DoorUnlockMessage::CHALLENGE_REQUEST:
                    handleChallengeRequest(duMessage);
                    break;
                case DoorUnlockMessage::CHALLENGE_CALCULATED:
                    handleChallengeCalculated(duMessage);
                    break;
                default:
                    iWarning() << "Unsupported stage" << stage;
                }

            } else {
                iWarning() << "Stage attribute missing";
                sendResult(duMessage->userId(), duMessage->doorId(), false);
            }
        } else {
            iWarning() << "Insufficient user rights" << duMessage->userId();
            sendResult(duMessage->userId(), duMessage->doorId(), false);
        }
    } else {
        iWarning() << "User could not be resolved" << duMessage->userId();
        sendResult(duMessage->userId(), duMessage->doorId(), false);
    }
}

void DoorUnlockManager::onChallengeMaintenance() {
    //QMutexLocker locker(&m_currentChallengeRequestsMutex);
    iInfo() << Q_FUNC_INFO;

    for (auto it = m_currentChallengeRequests.begin(); it != m_currentChallengeRequests.end();) {
        if (QDateTime::currentMSecsSinceEpoch() > it.value().ts + DU_CHALLENGE_TIMEOUT_MS) {
            iDebug() << "Clean up challenge" << it.key() << it->ts;
            it = m_currentChallengeRequests.erase(it);
        }
    }
}

void DoorUnlockManager::handleChallengeRequest(DoorUnlockMessage* duMessage) {
    //QMutexLocker locker(&m_currentChallengeRequestsMutex);

    QString initiatorId = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_INITIATOR_ID).toString();

    if (!initiatorId.isEmpty()) {       // TODO: maybe verify iid?
        if (!m_currentChallengeRequests.contains(duMessage->userId())) {

            ChallengeRequest req;
            req.ts = QDateTime::currentMSecsSinceEpoch();
            req.oth = QString::number(QRandomGenerator::global()->bounded((quint32) 10000, (quint32) 99999));

            QString userId = duMessage->userId();
            QString doorId = duMessage->doorId();
            m_currentChallengeRequests.insert(userId, req);

            QVariantMap values;
            values.insert(DoorUnlockMessage::DU_ATTRIB_STAGE, DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_CREATED);
            values.insert(DoorUnlockMessage::DU_ATTRIB_TS, req.ts);
            values.insert(DoorUnlockMessage::DU_ATTRIB_OTH, req.oth);
            values.insert(DoorUnlockMessage::DU_ATTRIB_INITIATOR_ID, initiatorId);
            DoorUnlockMessage responseMessage(userId, doorId, values);
            m_commManager->sendMessage(responseMessage);
            iInfo() << "Sending challenge created";
        } else {
            iWarning() << "Cannot create duplicate challenge";
            sendResult(duMessage->userId(), duMessage->doorId(), false);
        }
    } else {
        iWarning() << "No iid set";
        sendResult(duMessage->userId(), duMessage->doorId(), false);
    }
}

void DoorUnlockManager::handleChallengeCalculated(DoorUnlockMessage* duMessage) {
    //QMutexLocker locker(&m_currentChallengeRequestsMutex);

    QString userId = duMessage->userId();
    QString doorId = duMessage->doorId();

    QString initiatorId = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_INITIATOR_ID).toString();

    if (!initiatorId.isEmpty()) {       // TODO: maybe verify iid?
        if (m_currentChallengeRequests.contains(userId)) {
            if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_OTH)) {
                QString oth = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_OTH).toString();

                if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_TS)) {
                    qint64 ts = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_TS).toLongLong();

                    if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_RESULT_HASH)) {
                        QString resultHash = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_RESULT_HASH).toString();
                        QString expectedResultHash = calculateResultHash(ts, oth, userId, doorId);

                        if (resultHash == expectedResultHash) {
                            Q_EMIT(unlockDoor(doorId));
                            sendResult(userId, doorId, true, initiatorId);
                            iInfo() << "Challenge success";
                        } else {
                            iWarning() << "Challenge mismatch" << resultHash << " expected " << expectedResultHash;
                            sendResult(userId, doorId, false);
                        }
                    } else {
                        iWarning() << "Missing attribute" << DoorUnlockMessage::DU_ATTRIB_RESULT_HASH;
                    }
                } else {
                    iWarning() << "Missing attribute" << DoorUnlockMessage::DU_ATTRIB_TS;
                }
            } else {
                iWarning() << "Missing attribute" << DoorUnlockMessage::DU_ATTRIB_OTH;
            }

            // just clean up all the time
            m_currentChallengeRequests.remove(userId);
        } else {
            iWarning() << "Request not found or timeout";
            sendResult(userId, doorId, false);
        }
    } else {
        iWarning() << "No iid set";
        sendResult(userId, doorId, false);
    }
}

QString DoorUnlockManager::calculateResultHash(qint64 ts, QString oth, QString userId, QString doorId) {
    QCryptographicHash sha1(QCryptographicHash::Sha1);

    sha1.addData(QString::number(ts).toLatin1());
    sha1.addData(oth.toLatin1());
    sha1.addData(userId.toLatin1());
    sha1.addData(DoorUnlock::PSK.latin1());
    sha1.addData(doorId.toLatin1());

    return sha1.result().toBase64();
}

void DoorUnlockManager::sendResult(QString userId, QString doorId, bool success, QString initiatorId) {
    QVariantMap values;
    values.insert(DoorUnlockMessage::DU_ATTRIB_STAGE, success ? DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_SUCCESS : DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_FAILURE);
    values.insert(DoorUnlockMessage::DU_ATTRIB_INITIATOR_ID, initiatorId);
    DoorUnlockMessage duMessage(userId, doorId, values);
    m_commManager->sendMessage(duMessage);
}
