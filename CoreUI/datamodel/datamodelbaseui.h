#ifndef DATAMODELBASEUI_H
#define DATAMODELBASEUI_H

#include <QObject>
#include "identifyableui.h"
#include "datamodel/server/datamodelbase.h"

class DatamodelBaseUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit DatamodelBaseUI(QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> processorTasks READ processorTasks NOTIFY processorTasksChanged)
    Q_PROPERTY(QList<QObject*> values READ values NOTIFY valuesChanged)
    Q_PROPERTY(QList<QObject*> actors READ actors NOTIFY actorsChanged)

    QList<QObject*> processorTasks();
    QList<QObject*> values();
    QList<QObject*> actors();

private:
    DatamodelBase* m_datamodel;

    QList<QObject*> m_processorTasks;
    QList<QObject*> m_values;
    QList<QObject*> m_actors;

signals:
    void processorTasksChanged();
    void valuesChanged();
    void actorsChanged();

public slots:
};

#endif // DATAMODELBASEUI_H
