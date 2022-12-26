#ifndef KNOWNROOMUI_H
#define KNOWNROOMUI_H

#include <QObject>
#include "visualitembase.h"
#include "datamodel/server/meta/knownroom.h"
#include "value/valuebaseui.h"
#include "actor/actorbaseui.h"

class KnownRoomUI : public VisualItemBase
{
    Q_OBJECT
public:
    explicit KnownRoomUI(Identifyable *parent = nullptr);

    Q_PROPERTY(QString name READ name NOTIFY nameChanged)
    Q_PROPERTY(QList<QObject*> values READ values NOTIFY valuesChanged)
    Q_PROPERTY(QList<QObject*> actors READ actors NOTIFY actorsChanged)

    Q_INVOKABLE void addValue(ValueBaseUI* value);
    Q_INVOKABLE void addActor(ActorBaseUI* actor);

    QString name();
    QList<QObject*> values();
    QList<QObject*> actors();

protected:
    KnownRoom* m_knownRoom;
    QList<QObject*> m_values;
    QList<QObject*> m_actors;

signals:
    void nameChanged();
    void valuesChanged();
    void actorsChanged();

};

#endif // KNOWNROOMUI_H
