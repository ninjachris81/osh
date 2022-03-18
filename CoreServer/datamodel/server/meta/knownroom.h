#ifndef KNOWNROOM_H
#define KNOWNROOM_H

#include <QObject>
#include "serializableidentifyable.h"
#include "actor/actorbase.h"
#include "value/valuebase.h"

class KnownRoom : public SerializableIdentifyable
{
    Q_OBJECT
public:
    KnownRoom();
    explicit KnownRoom(QString id, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    void setName(QString name);
    QString name();

    void addActor(ActorBase* actor);
    void addValue(ValueBase* value);

    QMap<QString, ActorBase*> actors();
    QMap<QString, ValueBase*> values();

protected:
    QString m_name;
    QMap<QString, ActorBase*> m_actors;
    QMap<QString, ValueBase*> m_values;

signals:
    void nameChanged();

};

#endif // KNOWNROOM_H
