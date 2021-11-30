#include "modelprocessormanagerui.h"
#include "processor/scriptresultmessage.h"

QLatin1Literal ModelProcessorManagerUI::MANAGER_ID = QLatin1Literal("ModelProcessorManager");
ModelProcessorManagerUI * ModelProcessorManagerUI::m_qmlInstance = nullptr;

ModelProcessorManagerUI::ModelProcessorManagerUI(QObject *parent) : ManagerBase(parent)
{
    m_qmlInstance = this;
}

QObject* ModelProcessorManagerUI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return m_qmlInstance;
}

QString ModelProcessorManagerUI::id() {
    return MANAGER_ID;
}

void ModelProcessorManagerUI::init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(DatamodelManagerUI);

    m_datamodelManager = getManager<DatamodelManagerUI>(DatamodelManagerUI::MANAGER_ID);
}

MessageBase::MESSAGE_TYPE ModelProcessorManagerUI::getMessageType() {
    return MessageBase::MESSAGE_TYPE_SCRIPT_RESULT;
}

void ModelProcessorManagerUI::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
    ScriptResultMessage* srMessage = static_cast<ScriptResultMessage*>(msg);

    QListIterator<QObject*> it(m_datamodelManager->datamodel()->processorTasks());
    while(it.hasNext()) {
        ProcessorTaskUI* task = static_cast<ProcessorTaskUI*>(it.next());

        if (task->id() == srMessage->processorTaskId()) {
            task->setLastResult(srMessage->value());
            return;
        }
    }

    iWarning() << "Processor task" << srMessage->processorTaskId() << "not defined in datamodel";
}

QList<QObject*> ModelProcessorManagerUI::processorTasks() {
    return m_datamodelManager->datamodel()->processorTasks();
}
