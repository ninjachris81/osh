#include "controllerbase.h"

#include "controller/controllermanager.h"

ControllerBase::ControllerBase(ControllerManager *manager, QString id, QObject *parent) : Identifyable (id, parent), m_manager(manager)
{

}

void ControllerBase::setConfig(LocalConfig* config) {
    m_config = config;
}
