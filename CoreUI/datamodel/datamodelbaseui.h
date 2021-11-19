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

    QList<QObject*> processorTasks();
    QList<QObject*> values();

private:
    DatamodelBase* m_datamodel;

    QList<QObject*> m_processorTasks;
    QList<QObject*> m_values;

signals:
    void processorTasksChanged();
    void valuesChanged();

public slots:
};

#endif // DATAMODELBASEUI_H
