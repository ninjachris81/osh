#ifndef PROCESSORTASKUI_H
#define PROCESSORTASKUI_H

#include <QObject>
#include "identifyableui.h"

#include "processor/server/processortask.h"

class ProcessorTaskUI : public IdentifyableUI
{
    Q_OBJECT
public:
    explicit ProcessorTaskUI(Identifyable *parent = nullptr);

    Q_PROPERTY(QString scriptCode READ scriptCode NOTIFY scriptCodeChanged)
    Q_PROPERTY(qint64 scheduleInterval READ scheduleInterval NOTIFY scheduleIntervalChanged)
    Q_PROPERTY(qint64 lastExecution READ lastExecution NOTIFY lastExecutionChanged)
    Q_PROPERTY(QVariant lastResult READ lastResult NOTIFY lastResultChanged)

    QString scriptCode();
    qint64 scheduleInterval();
    qint64 lastExecution();
    QVariant lastResult();

    void setLastResult(QVariant lastResult);

private:
    ProcessorTask* m_processorTask;

signals:
    void scriptCodeChanged();
    void scheduleIntervalChanged();
    void lastExecutionChanged();
    void lastResultChanged();

public slots:
};

#endif // PROCESSORTASKUI_H
