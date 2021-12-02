#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QMap>
#include <QList>
#include "device/knowndevice.h"
#include "actor/actorbase.h"
#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "value/doublevalue.h"
#include "actor/digitalactor.h"
#include "processor/server/processortask.h"
#include "shared/units_qt.h"

#include "identifyable.h"

using namespace unit;

class DatamodelBase : public Identifyable
{
    Q_OBJECT
public:
    explicit DatamodelBase(QString id, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QMap<QString, KnownDevice *> knownDevices();
    QMap<QString, ValueBase*> values();
    QMap<QString, ActorBase*> actors();
    QMap<QString, ProcessorTask*> processorTasks();

    KnownDevice* addKnownDevice(QString id, QString serviceId, QString name);
    ValueGroup* addValueGroup(QString id);
    DigitalActor* addDigitalActor(ValueGroup* valueGroup, QString id, bool isAsync, ValueBase::VALUE_TIMEOUT timeout);
    BooleanValue* addBooleanValue(ValueGroup* valueGroup, QString id, ValueBase::VALUE_TIMEOUT timeout);
    DoubleValue* addDoubleValue(ValueGroup* valueGroup, QString id, UNIT_TYPE unitType, ValueBase::VALUE_TIMEOUT timeout);
    ProcessorTask* addProcessorTask(QString id, QString scriptCode, qint64 scheduleInterval = 0);

protected:
    QMap<QString, KnownDevice*> m_knownDevices;
    QMap<QString, ValueGroup*> m_valueGroups;
    QMap<QString, ValueBase*> m_values;
    QMap<QString, ActorBase*> m_actors;

    QMap<QString, ProcessorTask*> m_processorTasks;

signals:

public slots:
};

#endif // DATAMODELBASE_H
