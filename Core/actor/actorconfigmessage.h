#ifndef ACTORCONFIGMESSAGE_H
#define ACTORCONFIGMESSAGE_H

#include <QObject>
#include "communication/messagebase.h"
#include "shared/actor_qt.h"

class ActorConfigMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ActorConfigMessage(QString actorGroupId, QString actorId, QMap<QString, QVariant> values, QObject *parent = nullptr);


    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString actorGroupId();
    QString actorId();
    QString fullId();

    QMap<QString, QVariant> values();

protected:
    QString m_actorGroupId;
    QString m_actorId;

    QMap<QString, QVariant> m_values;

signals:

};

#endif // ACTORCONFIGMESSAGE_H
