#ifndef LOCALCONFIG_H
#define LOCALCONFIG_H

#include <QObject>
#include <QSettings>

#define CONFIG_VERSION 1

class Identifyable;     // fwddcl

class LocalConfig : public QObject
{
    Q_OBJECT
public:
    explicit LocalConfig(QObject *parent = nullptr);
    ~LocalConfig();

    void updateValue(QString key, QVariant value);
    void updateValue(Identifyable* entity, QString key, QVariant value);

    QVariant getValue(QString key, QVariant defaultValue);
    QVariant getValue(Identifyable* entity, QString key, QVariant defaultValue);

    QString getString(QString key, QString defaultValue);
    QString getString(Identifyable* entity, QString key, QString defaultValue);

    int getInt(QString key, int defaultValue);
    int getInt(Identifyable* entity, QString key, int defaultValue);

    bool getBool(QString key, bool defaultValue);
    bool getBool(Identifyable* entity, QString key, bool defaultValue);

    bool exists(QString key);
    bool exists(Identifyable* entity, QString key);

protected:
    QSettings* m_settings;

    QStringList keys();

signals:

public slots:
};

#endif // LOCALCONFIG_H
