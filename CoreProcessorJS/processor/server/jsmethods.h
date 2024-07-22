#ifndef JSMETHODS_H
#define JSMETHODS_H

#include <QObject>
#include "identifyable.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

class JSMethods : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit JSMethods(ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent = nullptr);

    Q_INVOKABLE QJsonValue getValue(QString fullId);

private:
    ValueManagerBase *m_valueManager;
    ActorManager *m_actorManager;

signals:

};

#endif // JSMETHODS_H
