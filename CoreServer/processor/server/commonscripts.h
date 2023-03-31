#ifndef COMMONSCRIPTS_H
#define COMMONSCRIPTS_H

#include <QObject>

#include "processor/server/scriptbase.h"
#include "value/valuebase.h"
#include "actor/actorbase.h"
#include "datamodel/datamodelbase.h"
#include "processor/server/localstorage.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

class SHARED_LIB_EXPORT CommonScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit CommonScripts(DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    //Q_INVOKABLE bool ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant actualInvalid, QJSValue function);

    Q_INVOKABLE bool applySwitchMotionLogic(QString lightActorFullId, QString inputSensorFullId, QString motionSensorFullId, QString brightnessSensorFullId, int brightnessThreshold, quint64 triggerTimeoutMs, quint64 motionSensorGracePeriodMs);

    Q_INVOKABLE bool initSwitchLogic(QString lightRelayActorFullId, QString inputSensorFullId, QString toggleActorFullId);

    Q_INVOKABLE bool applySwitchTimeoutLogic(QString toggleActorFullId, quint64 triggerTimeoutMs);

    Q_INVOKABLE bool applyTempValveLogic(QString tempFullId, QString tempTargetFullId, QString tempValveActorFullId, int adjustIntervalMs, double fullDeltaThresholdTemp = 5.0, int factorIntervalMs = 10000);

    Q_INVOKABLE bool applyMotionLogic(QString radarFullId, QString pirFullId, QString motionFullId);

    Q_INVOKABLE bool applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString motionFullId, quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo);

    Q_INVOKABLE bool initDoorRingLogic(QString inputSensorFullId, QString doorRingActorFullId);

    Q_INVOKABLE bool applyDoorRingTimeoutLogic(QString doorRingActorFullId, quint64 triggerTimeoutMs);

    Q_INVOKABLE bool isWithin(quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo);

    static QLatin1String INTERVAL_OFF_DURATIONS;
    static QLatin1String INTERVAL_ON_DURATIONS;
    static QLatin1String INTERVAL_LAST_CHANGES;
    static QLatin1String INTERVAL_STATES;

    static QLatin1String TIMOUT_LAST_TS;

    //Q_INVOKABLE void publishValue(QString fullId, QVariant value);
    Q_INVOKABLE void publishCmd(QString fullId, int cmd, QString reason);
    Q_INVOKABLE void publishCmd(QString fullId, int cmd, QVariant value, QString reason);

    Q_INVOKABLE void setupInterval(QString key, qulonglong durationOffMs, qulonglong durationOnMs, bool resetState = true);
    Q_INVOKABLE bool getIntervalState(QString key);
    Q_INVOKABLE void clearInterval(QString key);

    Q_INVOKABLE void setTimeout(QString key);
    Q_INVOKABLE bool isTimeout(QString key, quint64 timeoutMs, bool clearTimeoutIfTrue = true);
    Q_INVOKABLE quint64 getTimeout(QString key);
    Q_INVOKABLE void clearTimeout(QString key);

private slots:
    void onInitSwitchLogic_inputSensorValueChanged();
    void onInitSwitchLogic_toggleActorValueChanged();

    void initDoorRingLogic_inputSensorValueChanged();

private:
    DatamodelBase* m_datamodel;
    LocalStorage* m_localStorage;
    ValueManagerBase* m_valueManager;
    ActorManager* m_actorManager;

    //void publishValue(ValueBase* val, QVariant value);
    void publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QString reason);
    void publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QVariant value, QString reason);

signals:

public slots:
};

#endif // COMMONSCRIPTS_H
