#ifndef PROCESSORTASK_H
#define PROCESSORTASK_H

#include <QObject>
#include <QJSEngine>

#include "identifyable.h"

class ProcessorTask : public Identifyable
{
    Q_OBJECT
public:
    explicit ProcessorTask(QString id, QString scriptCode, qint64 scheduleInterval = 0, QObject *parent = nullptr);

    /*virtual*/ LogCat::LOGCAT logCat() override;

    QVariant run(QJSEngine* engine);

    QString scriptCode();
    qint64 scheduleInterval();
    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);
    void setLastExecutionNow();

private:
    QString m_scriptCode;
    qint64 m_scheduleInterval;
    qint64 m_lastExecution = 0;
    QVariant m_lastResult;

signals:
    void lastExecutionChanged();
    void lastResultChanged();

public slots:
};

#endif // PROCESSORTASK_H
