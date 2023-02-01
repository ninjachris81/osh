#ifndef DATAMODELBASEUI_H
#define DATAMODELBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "datamodel/server/datamodelbase.h"

class DatamodelBaseUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit DatamodelBaseUI(Identifyable *parent);

    Q_PROPERTY(QList<QObject*> processorTasks READ processorTasks NOTIFY processorTasksChanged)
    Q_PROPERTY(QList<QObject*> values READ values NOTIFY valuesChanged)
    Q_PROPERTY(QList<QObject*> actors READ actors NOTIFY actorsChanged)
    Q_PROPERTY(QList<QObject*> knownRooms READ knownRooms NOTIFY knownRoomsChanged)

    QList<QObject*> processorTasks();
    QList<QObject*> values();
    QList<QObject*> actors();
    QList<QObject*> knownRooms();

private:
    DatamodelBase* m_datamodel;

    QList<QObject*> m_processorTasks;
    QList<QObject*> m_values;
    QList<QObject*> m_actors;
    QList<QObject*> m_knownRooms;

signals:
    void processorTasksChanged();
    void valuesChanged();
    void actorsChanged();
    void knownRoomsChanged();

public slots:
};

#endif // DATAMODELBASEUI_H
