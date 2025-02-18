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

    Q_INVOKABLE bool initSwitchPresenceLogic(QString presenceId, QString toggleActorId, QString brightnessId, double brightnessThreshold, quint64 switchCooldownPeriodMs);

    Q_INVOKABLE bool applySwitchPresenceLogic(QString presenceId);

    Q_INVOKABLE bool initSwitchLogic(QString lightRelayActorFullId, QString inputSensorFullId, QString toggleActorFullId);

    Q_INVOKABLE bool initSwitchLogic2(QString lightRelayActorFullId, QString toggleActorFullId);

    Q_INVOKABLE bool applySwitchTimeoutLogic(QString toggleActorFullId, quint64 triggerTimeoutMs);

    Q_INVOKABLE bool applyTempValveLogic(QString tempFullId, QString tempTargetFullId, QString tempValveActorFullId, int adjustIntervalMs, double fullDeltaThresholdTemp = 5.0, int factorIntervalMs = 10000);

    Q_INVOKABLE bool initPresenceLogic(QString radarId, QString pirId, QString presenceId);

    Q_INVOKABLE bool applyPresenceLogic(QString presenceId, qint32 timeoutMs);

    Q_INVOKABLE bool applyShutterLogic(QString shutterFullId, QString shutterModeFullId, QString presenceFullId, quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo);

    Q_INVOKABLE bool initDoorRingLogic(QString inputSensorFullId, QString doorRingActorFullId);

    Q_INVOKABLE bool applyDoorRingTimeoutLogic(QString doorRingActorFullId, quint64 triggerTimeoutMs);

    Q_INVOKABLE bool initPlaySoundOnValue(QString valueEventId, QVariant playValue, QString soundActorId, QString soundValue);

    Q_INVOKABLE bool initPlaySoundOnValue2(QString valueEventId, QVariant playValue, QVariant stopValue, QString soundActorId, QString soundValue);

    Q_INVOKABLE bool initPlaySoundOnCmd(QString actorId, int cmdValue, QString soundActorId, QString soundValue);

private slots:
    void onInitSwitchPresenceLogic_presenceValueChanged();

    void onInitSwitchLogic_inputSensorValueChanged();
    void onInitSwitchLogic_toggleActorValueChanged();

    void onInitSwitchLogic2_toggleActorValueChanged();

    void onInitPresenceLogic_radarValueChanged();
    void onInitPresenceLogic_pirValueChanged();
    void onInitPresenceLogic_valueChanged(QObject *sender, QString presenceKey, QString valueKey);

    void onInitDoorRingLogic_inputSensorValueChanged();
    void onInitPlaySoundOnValue_valueChanged();
    void onInitPlaySoundOnCmd_triggeredCmd(actor::ACTOR_CMDS cmd);

private:
    void _onInitSwitchPresenceLogic_presenceValueChanged(BooleanValue *presenceSensor);

signals:

public slots:
};

#endif // COMMONSCRIPTS_H
