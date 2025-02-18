#include "controllerbase.h"

#include "controller/controllermanager.h"

ControllerBase::ControllerBase(ControllerManager *manager, QString id, QObject *parent) : QObject(parent), Identifyable(id), m_manager(manager)
{

}

LogCat::LOGCAT ControllerBase::logCat() {
    return LogCat::CONTROLLER;
}

void ControllerBase::setConfig(LocalConfig* config) {
    m_config = config;
}

/*
void ControllerBase::bindValueManager(ClientValueManager *clientValueManager, QList<ValueBase*> valueOrActors) {

    QListIterator<ValueBase*> it(valueOrActors);
    while(it.hasNext()) {
        ValueBase* valOrActor = it.next();
        clientValueManager->registerValue(valOrActor);
    }
}
*/
