#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QMap>
#include <QList>
#include "device/knowndevice.h"
#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "processor/server/processortask.h"

class DatamodelBase : public QObject
{
    Q_OBJECT
public:
    explicit DatamodelBase(QObject *parent = nullptr);

    QMap<QString, ValueBase*> values();
    QMap<QString, KnownDevice *> knownDevices();
    QMap<QString, ProcessorTask*> processorTasks();

protected:
    QMap<QString, KnownDevice*> m_knownDevices;
    QMap<QString, ValueGroup*> m_valueGroups;
    QMap<QString, ValueBase*> m_values;

    QMap<QString, ProcessorTask*> m_processorTasks;

signals:

public slots:
};

#endif // DATAMODELBASE_H
