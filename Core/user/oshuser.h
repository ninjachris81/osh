#ifndef OSHUSER_H
#define OSHUSER_H

#include <QObject>

#include "serializableidentifyable.h"

class OshUser : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    static QLatin1String USER_RIGHT_UNLOCK_DOOR;

    static QLatin1String PROPERTY_NAME;
    static QLatin1String PROPERTY_RIGHTS;

    explicit OshUser(QString id, QString name, QStringList rights, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QString name();
    QStringList rights();

private:
    QString m_name;
    QStringList m_rights;

signals:

};

#endif // OSHUSER_H
