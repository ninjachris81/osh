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

class CommonScripts : public ScriptBase
{
    Q_OBJECT
public:
    explicit CommonScripts(QJSEngine * engine, DatamodelBase* datamodel, LocalStorage* localStorage, QObject *parent = nullptr);

    Q_INVOKABLE bool ensureState(ValueBase* actualValue, ValueBase* expectedValue, QVariant actualInvalid, QJSValue function);

    Q_INVOKABLE bool applySwitchLogic(QString lightActorFullId, QString inputSensorFullId, QString motionSensorFullId, QString brightnessSensorFullId, int brightnessThreshold, quint64 triggerTimeoutMs, quint64 motionSensorGracePeriodMs);

private:
    QJSEngine * m_engine;
    DatamodelBase* m_datamodel;
    LocalStorage* m_localStorage;

signals:

public slots:
};

#endif // COMMONSCRIPTS_H
