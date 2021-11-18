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

    QList<QObject*> processorTasks();

private:
    DatamodelBase* m_datamodel;

    QList<QObject*> m_processorTasks;

signals:
    void processorTasksChanged();

public slots:
};

#endif // DATAMODELBASEUI_H
