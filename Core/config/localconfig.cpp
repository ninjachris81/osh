#include "localconfig.h"

#include <QDebug>
#include <QFile>
#include "identifyable.h"

LocalConfig::LocalConfig(QObject *parent) : QObject(parent)
{
    m_settings = new QSettings("config.ini", QSettings::IniFormat);
    qDebug() << "Config file" << m_settings->fileName();
    if (!QFile(m_settings->fileName()).exists()) {
        qDebug() << "Creating new config file";
        m_settings->setValue("config.version", CONFIG_VERSION);
        m_settings->sync();
    }
}

LocalConfig::~LocalConfig() {
    m_settings->sync();
}

QStringList LocalConfig::keys() {
    return m_settings->allKeys();
}

void LocalConfig::updateValue(QString key, QVariant value) {
    if (m_settings->contains(key)) {
        if (m_settings->value(key).type()!=value.type()) {
            if (!value.convert(m_settings->value(key).type())) {
                qWarning() << "Failed to convert" << value << "to" << m_settings->value(key).type();
            }
        }
    }

    m_settings->setValue(key, value);
}

void LocalConfig::updateValue(Identifyable* entity, QString key, QVariant value) {
    m_settings->beginGroup(entity->id());
    updateValue(key, value);
    m_settings->endGroup();
}


QVariant LocalConfig::getValue(QString key, QVariant defaultValue) {
    if (m_settings->contains(key)) {
        return m_settings->value(key);
    } else {
        m_settings->setValue(key, defaultValue);
        return defaultValue;
    }
}

QVariant LocalConfig::getValue(QString domain, QString key, QVariant defaultValue) {
    m_settings->beginGroup(domain);
    QVariant value = getValue(key, defaultValue);
    m_settings->endGroup();
    return value;
}


QVariant LocalConfig::getValue(Identifyable* entity, QString key, QVariant defaultValue) {
    return getValue(entity->id(), key, defaultValue);
}

QString LocalConfig::getString(QString key, QString defaultValue) {
    if (m_settings->contains(key)) {
        return m_settings->value(key).toString();
    } else {
        m_settings->setValue(key, defaultValue);
        return defaultValue;
    }
}


QString LocalConfig::getString(QString domain, QString key, QString defaultValue) {
    m_settings->beginGroup(domain);
    QString value = getString(key, defaultValue);
    m_settings->endGroup();
    return value;
}

QString LocalConfig::getString(Identifyable* entity, QString key, QString defaultValue) {
    return getString(entity->id(), key, defaultValue);
}

int LocalConfig::getInt(QString key, int defaultValue) {
    if (m_settings->contains(key)) {
        return m_settings->value(key).toInt();
    } else {
        m_settings->setValue(key, defaultValue);
        return defaultValue;
    }
}

int LocalConfig::getInt(Identifyable* entity, QString key, int defaultValue) {
    m_settings->beginGroup(entity->id());
    int value = getInt(key, defaultValue);
    m_settings->endGroup();
    return value;
}

bool LocalConfig::getBool(QString key, bool defaultValue) {
    if (m_settings->contains(key)) {
        return m_settings->value(key).toBool();
    } else {
        m_settings->setValue(key, defaultValue);
        return defaultValue;
    }
}

bool LocalConfig::getBool(Identifyable* entity, QString key, bool defaultValue) {
    m_settings->beginGroup(entity->id());
    bool value = getBool(key, defaultValue);
    m_settings->endGroup();
    return value;
}

bool LocalConfig::exists(QString key) {
    return m_settings->contains(key);
}

bool LocalConfig::exists(Identifyable* entity, QString key) {
    m_settings->beginGroup(entity->id());
    bool value = exists(key);
    m_settings->endGroup();
    return value;
}
