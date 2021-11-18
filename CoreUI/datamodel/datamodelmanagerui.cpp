#include "datamodelmanagerui.h"

DatamodelManagerUI * DatamodelManagerUI::m_instance = nullptr;

DatamodelManagerUI::DatamodelManagerUI(QObject *parent) : DatamodelManager(parent)
{
    m_instance = this;
}

QObject* DatamodelManagerUI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return m_instance;
}

DatamodelBaseUI* DatamodelManagerUI::datamodel() {
    delete m_datamodel;
    m_datamodel = new DatamodelBaseUI(DatamodelManager::datamodel());
    return m_datamodel;
}
