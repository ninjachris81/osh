#ifndef KNOWNROOM_H
#define KNOWNROOM_H

#include <QObject>
#include "identifyable.h"
#include "actor/actorbase.h"
#include "value/valuebase.h"

class KnownRoom : public Identifyable
{
    Q_OBJECT
public:
    explicit KnownRoom(QString id, QObject *parent = nullptr);

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
