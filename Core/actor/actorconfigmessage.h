#ifndef ACTORCONFIGMESSAGE_H
#define ACTORCONFIGMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"
#include "shared/actor_qt.h"

class SHARED_LIB_EXPORT ActorConfigMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ActorConfigMessage(QString actorGroupId, QString actorId, QVariantMap values, QObject *parent = nullptr);


    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString actorGroupId();
    QString actorId();
    QString fullId();

    QVariantMap values();

protected:
    QString m_actorGroupId;
    QString m_actorId;

    QVariantMap m_values;

signals:

};

#endif // ACTORCONFIGMESSAGE_H
