#include "logmanagerui.h"
#include "log/logentryui.h"

LogManagerUI * LogManagerUI::m_qmlInstance = nullptr;

LogManagerUI::LogManagerUI(QObject *parent) : LogManager(parent)
{
    m_qmlInstance = this;
    connect(this, &LogManager::logMessage, this, &LogManagerUI::onLogMessage);
    connect(&m_updateTimer, &QTimer::timeout, this, [this] () {
        if (m_logHasChanged) {
            m_logHasChanged = false;
            Q_EMIT(logsChanged());
        }
    });
}

void LogManagerUI::init(LocalConfig* config) {
    LogManager::init(config);

    m_logSize = config->getInt("log.entryBufferSize", 100);
    m_updateTimer.start(1000);
}


QList<QObject*> LogManagerUI::logs() {
    return m_logs;
}

void LogManagerUI::onLogMessage(QtMsgType type, QString deviceId, QString msg) {
    m_logs.insert(0, new LogEntryUI(deviceId, msgTypeToString(type), msg));

    if (m_logs.size() > m_logSize) {
        m_logs.removeLast();
    }

    m_logHasChanged = true;
}

QObject* LogManagerUI::qmlInstance(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    return m_qmlInstance;
}
