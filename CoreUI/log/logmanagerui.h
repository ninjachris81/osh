#ifndef LOGMANAGERUI_H
#define LOGMANAGERUI_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

#include "log/logmanager.h"

class LogManagerUI : public LogManager
{
    Q_OBJECT
public:
    explicit LogManagerUI(QObject *parent = nullptr);

    Q_PROPERTY(QList<QObject*> logs READ logs NOTIFY logsChanged)

    /*virtual*/ void init(LocalConfig* config) override;

    QList<QObject*> logs();

    static QObject *qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine);

private:
    QList<QObject*> m_logs;
    quint16 m_logSize;
    bool m_logHasChanged = false;
    QTimer m_updateTimer;

    static LogManagerUI* m_qmlInstance;

private slots:
    void onLogMessage(QtMsgType type, QString deviceId, QString msg);

signals:
    void logsChanged();

public slots:
};

#endif // LOGMANAGERUI_H
