#include "doorunlockmanager.h"

#include <QDateTime>
#include <QRandomGenerator>
#include <QCryptographicHash>

#include "macros.h"
#include "user/user.h"

QLatin1String DoorUnlockManager::MANAGER_ID = QLatin1String("DoorUnlockManager");
QLatin1String DoorUnlockManager::PSK = QLatin1String("q7XtfMBWAmKYWUekFPxS");

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

    m_currentChallengeRequestsTimer.start();
}

MessageBase::MESSAGE_TYPE DoorUnlockManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_DOOR_UNLOCK;
}

void DoorUnlockManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    DoorUnlockMessage* duMessage = static_cast<DoorUnlockMessage*>(msg);

    // first, check if user is allowed
    User* user = m_userManager->getUser(duMessage->userId());
    if (user != nullptr) {
        if (user->rights().contains(User::USER_RIGHT_UNLOCK_DOOR)) {
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
            }
        } else {
            iWarning() << "Insufficient user rights" << duMessage->userId();
        }
        user->deleteLater();
    } else {
        iWarning() << "User could not be resolved" << duMessage->userId();
    }
}

void DoorUnlockManager::onChallengeMaintenance() {
    QMutexLocker locker(&m_currentChallengeRequestsMutex);

    for (auto it = m_currentChallengeRequests.begin(); it != m_currentChallengeRequests.end();) {
        if (QDateTime::currentMSecsSinceEpoch() > it.value().ts + DU_CHALLENGE_TIMEOUT_MS) {
            iDebug() << "Clean up challenge" << it.key() << it->ts;
            it = m_currentChallengeRequests.erase(it);
        }
    }
}

void DoorUnlockManager::handleChallengeRequest(DoorUnlockMessage* duMessage) {
    QMutexLocker locker(&m_currentChallengeRequestsMutex);

    if (!m_currentChallengeRequests.contains(duMessage->userId())) {

        ChallengeRequest req;
        req.ts = QDateTime::currentMSecsSinceEpoch();
        req.oth = QString::number(QRandomGenerator::global()->bounded((quint32) 10000, (quint32) 99999));

        m_currentChallengeRequests.insert(duMessage->userId(), req);

        QVariantMap values;
        values.insert(DoorUnlockMessage::DU_ATTRIB_STAGE, DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_CREATED);
        values.insert(DoorUnlockMessage::DU_ATTRIB_TS, req.ts);
        values.insert(DoorUnlockMessage::DU_ATTRIB_OTH, req.oth);
        DoorUnlockMessage responseMessage(duMessage->userId(), duMessage->doorId(), values);
        m_commManager->sendMessage(responseMessage);
    } else {
        sendResult(duMessage->userId(), duMessage->doorId(), false);
        iWarning() << "Cannot create duplicate challenge";
    }
}

void DoorUnlockManager::handleChallengeCalculated(DoorUnlockMessage* duMessage) {
    QMutexLocker locker(&m_currentChallengeRequestsMutex);

    if (m_currentChallengeRequests.contains(duMessage->userId())) {
        if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_OTH)) {
            QString oth = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_OTH).toString();

            if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_TS)) {
                qint64 ts = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_TS).toLongLong();

                if (duMessage->values().contains(DoorUnlockMessage::DU_ATTRIB_RESULT_HASH)) {
                    QString resultHash = duMessage->values().value(DoorUnlockMessage::DU_ATTRIB_RESULT_HASH).toString();
                    QString expectedResultHash = calculateResultHash(ts, oth, duMessage->userId(), duMessage->doorId());

                    if (resultHash == expectedResultHash) {
                        Q_EMIT(unlockDoor(duMessage->doorId()));
                        iDebug() << "Challenge success";
                        sendResult(duMessage->userId(), duMessage->doorId(), true);
                    } else {
                        iWarning() << "Challenge mismatch" << resultHash << " expected " << expectedResultHash;
                        sendResult(duMessage->userId(), duMessage->doorId(), false);
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
        m_currentChallengeRequests.remove(duMessage->userId());
    } else {
        iWarning() << "Request not found or timeout";
        sendResult(duMessage->userId(), duMessage->doorId(), false);
    }
}

QString DoorUnlockManager::calculateResultHash(qint64 ts, QString oth, QString userId, QString doorId) {
    QCryptographicHash sha1(QCryptographicHash::Sha1);

    sha1.addData(QString::number(ts).toLatin1());
    sha1.addData(oth.toLatin1());
    sha1.addData(userId.toLatin1());
    sha1.addData(PSK.latin1());
    sha1.addData(doorId.toLatin1());

    return sha1.result().toBase64();
}

void DoorUnlockManager::sendResult(QString userId, QString doorId, bool success) {
    QVariantMap values;
    values.insert(DoorUnlockMessage::DU_ATTRIB_STAGE, success ? DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_SUCCESS : DoorUnlockMessage::DU_AUTH_STAGE::CHALLENGE_FAILURE);
    DoorUnlockMessage duMessage(userId, doorId, values);
    m_commManager->sendMessage(duMessage);
}