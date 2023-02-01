#ifndef USER_H
#define USER_H

#include <QObject>
#include <QSqlRecord>

#include "serializableidentifyable.h"

class User : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static QLatin1String USER_RIGHT_UNLOCK_DOOR;

    static QLatin1String USER_ID;
    static QLatin1String USER_DISPLAY_NAME;
    static QLatin1String USER_RIGHTS;

    explicit User(QString id, QObject *parent = nullptr);

    explicit User(QSqlRecord record, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QStringList rights();
    QString displayName();

private:
    QString m_displayName;
    QStringList m_rights;

signals:

};

#endif // USER_H
