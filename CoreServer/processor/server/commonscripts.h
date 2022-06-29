#ifndef COMMONSCRIPTS_H
#define COMMONSCRIPTS_H

#include <QObject>
#include <QJSValue>
#include <QJSEngine>
#include "processor/server/scriptbase.h"
#include "value/valuebase.h"
#include "actor/actorbase.h"
#include "datamodel/server/datamodelbase.h"
#include "processor/server/localstorage.h"
#include "value/valuemanagerbase.h"

class CommonScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit CommonScripts(QJSEngine * engine, DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, QObject *parent = nullptr);

    Q_INVOKABLE bool ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant actualInvalid, QJSValue function);

    Q_INVOKABLE bool applySwitchMotionLogic(QString lightActorFullId, QString inputSensorFullId, QString motionSensorFullId, QString brightnessSensorFullId, int brightnessThreshold, quint64 triggerTimeoutMs, quint64 motionSensorGracePeriodMs);

    Q_INVOKABLE bool applySwitchLogic(QString lightActorFullId, QString inputSensorFullId, quint64 triggerTimeoutMs);

    Q_INVOKABLE bool applyTempValveLogic(QString tempFullId, QString tempTargetFullId, QString tempValveActorFullId, int adjustIntervalMs, double fullDeltaThresholdTemp = 5.0, int factorIntervalMs = 10000);

    Q_INVOKABLE bool applyMotionLogic(QString radarFullId, QString pirFullId, QString motionFullId);

    Q_INVOKABLE bool applyShutterLogic(QString shutterFullId, QString motionFullId, quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo);

    static QLatin1String INTERVAL_OFF_DURATIONS;
    static QLatin1String INTERVAL_ON_DURATIONS;
    static QLatin1String INTERVAL_LAST_CHANGES;
    static QLatin1String INTERVAL_STATES;

    Q_INVOKABLE void publishValue(QString fullId, QVariant value);

    Q_INVOKABLE void setupInterval(QString key, qulonglong durationOffMs, qulonglong durationOnMs, bool resetState = true);
    Q_INVOKABLE bool getIntervalState(QString key);
    Q_INVOKABLE void clearInterval(QString key);

private:
    QJSEngine * m_engine;
    DatamodelBase* m_datamodel;
    LocalStorage* m_localStorage;
    ValueManagerBase* m_valueManager;

    void publishValue(ValueBase* val, QVariant value);

signals:

public slots:
};

#endif // COMMONSCRIPTS_H
