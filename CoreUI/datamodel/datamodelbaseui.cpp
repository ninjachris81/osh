#include "datamodelbaseui.h"

#include <QMapIterator>

#include "processor/processortaskui.h"
#include "value/valuebaseui.h"
#include "actor/actorbaseui.h"
#include "datamodel/server/meta/knownroomui.h"

DatamodelBaseUI::DatamodelBaseUI(Identifyable *parent) : IdentifyableUI(parent)
{
    m_datamodel = static_cast<DatamodelBase*>(parent);

    QMapIterator<QString, ProcessorTaskBase*> it(m_datamodel->processorTasks());
    while(it.hasNext()) {
        it.next();
        m_processorTasks.append(new ProcessorTaskUI(it.value()));
    }

    QMapIterator<QString, ValueBase*> it2(m_datamodel->values());
    while(it2.hasNext()) {
        it2.next();
        m_values.append(new ValueBaseUI(it2.value()));
    }

    QMapIterator<QString, ActorBase*> it3(m_datamodel->actors());
    while(it3.hasNext()) {
        it3.next();
        m_actors.append(new ActorBaseUI(it3.value()));
    }

    QMapIterator<QString, KnownRoom*> it4(m_datamodel->knownRooms());
    while(it4.hasNext()) {
        it4.next();
        m_knownRooms.append(new KnownRoomUI(it4.value()));
    }
}

QList<QObject*> DatamodelBaseUI::processorTasks() {
    return m_processorTasks;
}

QList<QObject*> DatamodelBaseUI::values() {
    return m_values;
}

QList<QObject*> DatamodelBaseUI::actors() {
    return m_actors;
}

QList<QObject*> DatamodelBaseUI::knownRooms() {
    return m_knownRooms;
}
