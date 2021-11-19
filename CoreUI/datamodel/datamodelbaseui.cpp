#include "datamodelbaseui.h"

#include <QMapIterator>

#include "processor/processortaskui.h"
#include "value/valuebaseui.h"

DatamodelBaseUI::DatamodelBaseUI(QObject *parent) : IdentifyableUI(parent)
{
    m_datamodel = static_cast<DatamodelBase*>(parent);
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

QList<QObject*> DatamodelBaseUI::values() {
    m_values.clear();

    QMapIterator<QString, ValueBase*> it(m_datamodel->values());
    while(it.hasNext()) {
        it.next();
        m_values.append(new ValueBaseUI(it.value()));
    }

    return m_values;
}
