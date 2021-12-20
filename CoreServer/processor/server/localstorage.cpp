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
