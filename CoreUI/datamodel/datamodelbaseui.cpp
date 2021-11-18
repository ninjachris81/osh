#include "datamodelbaseui.h"

#include <QMapIterator>

#include "processor/processortaskui.h"

DatamodelBaseUI::DatamodelBaseUI(QObject *parent) : IdentifyableUI(parent)
{
    m_datamodel = static_cast<DatamodelBase*>(parent);
    processorTasks();
}

QList<QObject*> DatamodelBaseUI::processorTasks() {
    m_processorTasks.clear();

    QMapIterator<QString, ProcessorTask*> it(m_datamodel->processorTasks());
    while(it.hasNext()) {
        it.next();
        m_processorTasks.append(new ProcessorTaskUI(it.value()));
    }

    return m_processorTasks;
}
