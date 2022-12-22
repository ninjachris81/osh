#ifndef USER_H
#define USER_H

#include <QObject>

#include "serializableidentifyable.h"

class User : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static QLatin1String USER_RIGHT_UNLOCK_DOOR;

    explicit User(QString id, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QStringList rights();

private:
    QStringList m_rights;

signals:

};

#endif // USER_H
