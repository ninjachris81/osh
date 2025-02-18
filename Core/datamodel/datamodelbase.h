#ifndef DATAMODELBASE_H
#define DATAMODELBASE_H

#include <QObject>

#include <QMap>
#include <QList>

#include "actor/audioplaybackactor.h"
#include "actor/dooractor.h"
#include "actor/toggleactor.h"
#include "actor/valueactor.h"
#include "processor/processorvariable.h"
#include "sharedlib.h"

#include "device/knowndevice.h"
#include "actor/actorbase.h"
#include "user/oshuser.h"
#include "value/enumvalue.h"
#include "value/valuegroup.h"
#include "value/valuebase.h"
#include "value/doublevalue.h"
#include "value/integervalue.h"
#include "value/longvalue.h"
#include "value/stringvalue.h"
#include "actor/digitalactor.h"
#include "actor/shutteractor.h"
#include "processor/processortaskbase.h"
#include "processor/processortaskfactory.h"
#include "shared/units_qt.h"

#include "identifyable.h"
#include "datamodel/meta/knownroom.h"
#include "datamodel/meta/knownarea.h"

using namespace unit;

class SHARED_LIB_EXPORT DatamodelBase : public QObject, public Identifyable
{
    Q_OBJECT
public:
    explicit DatamodelBase(QString id, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    void setProcessorTaskFactory(ProcessorTaskFactory* processorTaskFactory);

    QList<ValueGroup*> valueGroups();
    ValueGroup* valueGroup(QString id);

    ValueBase* value(QString valueFullId);
    QMap<QString, ValueBase*> values();
    QMap<QString, ValueBase*> values(QString valueGroupId);

    ActorBase* actor(QString actorFullId);
    QMap<QString, ActorBase*> actors();
    QMap<QString, ActorBase*> actors(QString valueGroupId);

    QMap<QString, KnownDevice *> knownDevices();
    QMap<QString, ProcessorTaskBase*> processorTasks();
    QMap<QString, KnownRoom*> knownRooms();

    QMap<QString, OshUser*> users();

    KnownDevice* addKnownDevice(QString id, QString serviceId, QString name);
    ValueGroup* addValueGroup(QString id);
    ToggleActor* addToggleActor(ValueGroup* valueGroup, QString id);
    DigitalActor* addDigitalActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool isAsync);
    ShutterActor* addShutterActor(ValueGroup* valueGroupState, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, bool tiltSupport, int fullCloseDuration, int fullTiltDuration);
    ValueActor* addValueActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, QVariant::Type typeHint);
    AudioPlaybackActor* addAudioPlaybackActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, QString audioDeviceIds, QString audioActivationRelayId, float audioVolume, QString audioVolumeId, QString audioDefaultUrl, QString audioUrlId, QString audioCurrentTitleId, QString audioName);
    DoorActor* addDoorActor(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);

    BooleanValue* addBooleanValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);
    IntegerValue* addIntegerValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);
    LongValue* addLongValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);
    DoubleValue* addDoubleValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);
    StringValue* addStringValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout);
    EnumValue* addEnumValue(ValueGroup* valueGroup, QString id, VALUE_TYPE valueType, ValueBase::VALUE_TIMEOUT timeout, int enumCount);
    ProcessorVariable* addProcessorVariable(QString id, QString value);
    //ProcessorTaskBase* addProcessorTask(QString groupId, QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, QString scriptCode, QString runCondition = "", qint64 scheduleInterval = ProcessorTaskBase::INTERVAL_REALTIME, bool publishResult = false, bool isEnabled = true);
    ProcessorTaskBase* addProcessorTask(QString groupId, QString id, ProcessorTaskBase::ProcessorTaskType taskType, ProcessorTaskBase::ProcessorTaskTriggerType taskTriggerType, int functionCode, QStringList params, qint64 scheduleInterval = ProcessorTaskBase::INTERVAL_REALTIME, bool isEnabled = true);
    KnownRoom* addKnownRoom(KnownArea *knownArea, QString id, QString name);

    OshUser* addUser(QString id, QString name, QStringList rights);

    KnownArea* addKnownArea(QString id, QString name);
    KnownArea* knownArea(QString id);

protected:
    ProcessorTaskFactory* m_processorTaskFactory = nullptr;

    QMap<QString, KnownDevice*> m_knownDevices;
    QMap<QString, ValueGroup*> m_valueGroups;
    QMap<QString, ValueBase*> m_values;
    QMap<QString, ActorBase*> m_actors;
    QMap<QString, KnownRoom*> m_knownRooms;
    QMap<QString, KnownArea*> m_knownAreas;

    QMap<QString, ProcessorVariable*> m_processorVariables;
    QMap<QString, ProcessorTaskBase*> m_processorTasks;

    QMap<QString, OshUser*> m_users;

private:

signals:
    void datamodelContentChanged();

public slots:
};

#endif // DATAMODELBASE_H
