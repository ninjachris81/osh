#pragma once

#include <QObject>
#include <QMultiMap>
#include <QVariant>

#include <functional>

#include "sharedlib.h"

class SHARED_LIB_EXPORT TaskStorage : public QObject
{
    Q_OBJECT
public:
    explicit TaskStorage(QObject *parent = nullptr);

    void registerExecution(QObject* triggerObj, std::function<void(QVariantList)> executionFunction);

    void triggerExecution(QObject* triggerObj, QVariantList params);

private:
    QMultiMap<QObject*, std::function<void(QVariantList)>> m_executionTasks;

signals:

};

