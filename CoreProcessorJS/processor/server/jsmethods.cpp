#include "jsmethods.h"

JSMethods::JSMethods(ValueManagerBase *valueManager, ActorManager* actorManager, QObject *parent)
    : QObject{parent}, m_valueManager(valueManager), m_actorManager(actorManager)
{

}

QJsonValue JSMethods::getValue(QString fullId) {
    return QJsonValue::fromVariant(m_valueManager->getValue(fullId)->rawValue());
}
