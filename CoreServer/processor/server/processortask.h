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

    void run(QJSEngine* engine);

    QString scriptCode();
    qint64 scheduleInterval();
    qint64 lastExecution();

private:
    QString m_scriptCode;
    qint64 m_scheduleInterval;
    qint64 m_lastExecution = 0;

signals:

public slots:
};

#endif // PROCESSORTASK_H
