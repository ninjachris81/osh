#pragma once

#include <QObject>

#include "identifyable.h"

class OshUser : public QObject, public Identifyable
{
    Q_OBJECT
public:
    static QLatin1String USER_RIGHT_UNLOCK_DOOR;

    static QLatin1String PROPERTY_NAME;
    static QLatin1String PROPERTY_RIGHTS;

    explicit OshUser(QString id, QString name, QStringList rights, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QString name();
    QStringList rights();

private:
    QString m_name;
    QStringList m_rights;

signals:

};

