#include "taskstorage.h"

TaskStorage::TaskStorage(QObject *parent)
    : QObject{parent}
{

}

void TaskStorage::registerExecution(QObject* triggerObj, std::function<void(QVariantList)> executionFunction) {
    m_executionTasks.insert(triggerObj, executionFunction);
}

void TaskStorage::triggerExecution(QObject* triggerObj, QVariantList params) {
    for (auto executionFunction : m_executionTasks.values(triggerObj)) {
        executionFunction(params);
    }
}
