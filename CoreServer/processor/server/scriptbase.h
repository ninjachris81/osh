#ifndef SCRIPTBASE_H
#define SCRIPTBASE_H

#include <QObject>
#include <QTime>
#include "identifyable.h"
#include "processor/server/scriptbase.h"
#include "value/valuebase.h"
#include "actor/actorbase.h"
#include "datamodel/datamodelbase.h"
#include "processor/server/localstorage.h"
#include "value/valuemanagerbase.h"
#include "actor/actormanager.h"

class ScriptBase : public QObject, public Identifyable
{
    Q_OBJECT
public:

    static QLatin1String INTERVAL_OFF_DURATIONS;
    static QLatin1String INTERVAL_ON_DURATIONS;
    static QLatin1String INTERVAL_LAST_CHANGES;
    static QLatin1String INTERVAL_STATES;

    static QLatin1String TIMOUT_LAST_TS;

    explicit ScriptBase(QString name, DatamodelBase* datamodel, LocalStorage* localStorage, ValueManagerBase* valueManager, ActorManager *actorManager, QObject *parent = nullptr);

    LogCat::LOGCAT logCat();

    Q_INVOKABLE bool isWithin(quint8 hourFrom, quint8 minuteFrom, quint8 hourTo, quint8 minuteTo, QTime referenceNow = QTime::currentTime());

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

protected:
    DatamodelBase* m_datamodel;
    LocalStorage* m_localStorage;
    ValueManagerBase* m_valueManager;
    ActorManager* m_actorManager;

    void publishValue(ValueBase* val, QVariant value);
    void publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QString reason);
    void publishCmd(ActorBase* actor, actor::ACTOR_CMDS cmd, QVariant value, QString reason);

private slots:

signals:

public slots:
};

#endif // SCRIPTBASE_H
