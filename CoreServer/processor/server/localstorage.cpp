#include "localstorage.h"

LocalStorage::LocalStorage(QObject *parent)
    : QObject{parent}
{

}

QString LocalStorage::getId(QString method, QString key, QString uniqueId) {
    return method + "_" + key + "_" + uniqueId;
}

bool LocalStorage::contains(QString method, QString key, QString uniqueId) {
    return m_values.contains(getId(method, key, uniqueId));
}

QVariant LocalStorage::get(QString method, QString key, QString uniqueId, QVariant defaultValue) {
    return m_values.value(getId(method, key, uniqueId), defaultValue);
}

void LocalStorage::set(QString method, QString key, QString uniqueId, QVariant value) {
    m_values.insert(getId(method, key, uniqueId), value);
}

void LocalStorage::unset(QString method, QString key, QString uniqueId) {
    m_values.remove(getId(method, key, uniqueId));
}

bool LocalStorage::containsObject(QString method, QString key, QString uniqueId) {
    return m_objects.contains(getId(method, key, uniqueId));
}

void LocalStorage::setObject(QString method, QString key, QString uniqueId, QObject* obj) {
    m_objects.insert(getId(method, key, uniqueId), obj);
}

QObject* LocalStorage::getObject(QString method, QString key, QString uniqueId) {
    return m_objects.value(getId(method, key, uniqueId));
}

void LocalStorage::unsetObject(QString method, QString key, QString uniqueId) {
    m_objects.remove(getId(method, key, uniqueId));
}
