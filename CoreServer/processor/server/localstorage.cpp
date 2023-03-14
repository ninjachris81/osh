#include "localstorage.h"

LocalStorage::LocalStorage(QObject *parent)
    : QObject{parent}
{

}

bool LocalStorage::contains(QString key) {
    return m_values.contains(key);
}

QVariant LocalStorage::get(QString key, QVariant defaultValue) {
    return m_values.value(key, defaultValue);
}

void LocalStorage::set(QString key, QVariant value) {
    m_values.insert(key, value);
}

void LocalStorage::unset(QString key) {
    m_values.remove(key);
}

void LocalStorage::setObject(QString key, QObject* obj) {
    m_objects.insert(key, obj);
}

QObject* LocalStorage::getObject(QString key) {
    return m_objects.value(key);
}

void LocalStorage::unsetObject(QString key) {
    m_objects.remove(key);
}
