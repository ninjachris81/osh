#ifndef KNOWNAREA_H
#define KNOWNAREA_H

#include <QObject>

#include "sharedlib.h"

#include "identifyable.h"
#include "datamodel/meta/knownroom.h"

class SHARED_LIB_EXPORT KnownArea : public QObject, public Identifyable
{
    Q_OBJECT
public:
    static QLatin1String PROPERTY_NAME;

    KnownArea();
    explicit KnownArea(QString id, QObject *parent = nullptr);

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
