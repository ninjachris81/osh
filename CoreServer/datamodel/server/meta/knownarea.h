#ifndef KNOWNAREA_H
#define KNOWNAREA_H

#include <QObject>

#include "sharedlib.h"

#include "serializableidentifyable.h"
#include "datamodel/server/meta/knownroom.h"

class SHARED_LIB_EXPORT KnownArea : public QObject, public SerializableIdentifyable
{
    Q_OBJECT
public:
    KnownArea();
    explicit KnownArea(QString id, QObject *parent = nullptr);

    /*virtual*/ void serialize(QJsonObject &obj) override;

    /*virtual*/ void deserialize(QJsonObject obj) override;

    /*virtual*/ QString getClassName() override;

    void setName(QString name);
    QString name();

    void addKnownRoom(KnownRoom* knownRoom);

    QMap<QString, KnownRoom*> knownRooms();

protected:
    QString m_name;
    QMap<QString, KnownRoom*> m_knownRooms;


signals:
    void nameChanged();
};

#endif // KNOWNAREA_H
