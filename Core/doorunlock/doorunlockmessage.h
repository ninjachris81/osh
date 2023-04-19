#ifndef DOORUNLOCKMESSAGE_H
#define DOORUNLOCKMESSAGE_H

#include <QObject>

#include "communication/messagebase.h"
#include "shared/actor_qt.h"

class DoorUnlockMessage : public MessageBase
{
    Q_OBJECT
public:
    enum DU_AUTH_STAGE {
        CHALLENGE_REQUEST,
        CHALLENGE_CREATED,
        CHALLENGE_CALCULATED,
        CHALLENGE_SUCCESS,
        CHALLENGE_FAILURE
    };

    static QLatin1String DU_ATTRIB_STAGE;
    static QLatin1String DU_ATTRIB_TS;
    static QLatin1String DU_ATTRIB_OTH;
    static QLatin1String DU_ATTRIB_RESULT_HASH;
    static QLatin1String DU_ATTRIB_DOOR_ID;
    static QLatin1String DU_ATTRIB_INITIATOR_ID;

    explicit DoorUnlockMessage(QString userId, QString doorId, QVariantMap values, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString userId();

    QString doorId();

    QVariantMap values();

private:
    QString m_userId;
    QString m_doorId;
    QVariantMap m_values;

signals:

};

#endif // DOORUNLOCKMESSAGE_H
