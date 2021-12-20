#include "logmanager.h"

#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <stdio.h>

#include "communication/communicationmanagerbase.h"
#include "log/logmessage.h"
#include "shared/log.h"

QLatin1String LogManager::MANAGER_ID = QLatin1String("LogManager");

LogManager* LogManager::m_instance = nullptr;

LogManager::LogManager(QObject *parent) : ManagerBase(parent)
{
}

void LogManager::init(LocalConfig *config) {
    m_instance = this;
    qInstallMessageHandler(&LogManager::messageHandler);

    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(CommunicationManagerBase);
    m_commManager = getManager<CommunicationManagerBase>(CommunicationManagerBase::MANAGER_ID);

    REQUIRE_MANAGER(DeviceDiscoveryManagerBase);
    m_ddManager = getManager<DeviceDiscoveryManagerBase>(DeviceDiscoveryManagerBase::MANAGER_ID);

    if (config->getBool("log.debug", false)) m_typeFilter.append(QtMsgType::QtDebugMsg);
    if (config->getBool("log.info", false)) m_typeFilter.append(QtMsgType::QtInfoMsg);
    if (config->getBool("log.warn", true)) m_typeFilter.append(QtMsgType::QtWarningMsg);
    if (config->getBool("log.critical", true)) m_typeFilter.append(QtMsgType::QtCriticalMsg);
    if (config->getBool("log.fatal", true)) m_typeFilter.append(QtMsgType::QtFatalMsg);
}

QString LogManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE LogManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_LOG;
}

void LogManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;

    LogMessage* logMsg = static_cast<LogMessage*>(msg);
    Q_EMIT(logMessage(logMsg->logType(), logMsg->deviceId(), logMsg->message()));
}

void LogManager::publishLog(QtMsgType type, QString msg) {
    if (m_typeFilter.contains(type)) {
        LogMessage logMsg(m_ddManager->device()->fullId(), type, msg);
        m_commManager->sendMessage(logMsg);
    }
}

void LogManager::registerManager(ManagerBase* manager) {
    m_managers.insert(manager->id(), manager);
}

QString LogManager::msgTypeToString(QtMsgType type) {
    switch (type) {
    case QtDebugMsg: return LOG_TYPE_DEBUG;
    case QtInfoMsg: return LOG_TYPE_INFO;
    case QtWarningMsg: return LOG_TYPE_WARNING;
    case QtCriticalMsg: return LOG_TYPE_CRITICAL;
    case QtFatalMsg: return LOG_TYPE_FATAL;
    }
}

QtMsgType LogManager::stringToMsgType(QString type) {
    if(type==LOG_TYPE_DEBUG) return QtDebugMsg;
    if(type==LOG_TYPE_INFO) return QtInfoMsg;
    if(type==LOG_TYPE_WARNING) return QtWarningMsg;
    if(type==LOG_TYPE_CRITICAL) return QtCriticalMsg;
    if(type==LOG_TYPE_FATAL) return QtFatalMsg;
    return QtDebugMsg;
}

void LogManager::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();

    if (m_instance != nullptr) {
        m_instance->publishLog(type, msg);
    }

    switch (type) {
    case QtDebugMsg:
        fprintf(stdout, "D: [%s] (%s:%u, %s)\n", context.category, localMsg.constData(), context.line, context.function);
        break;
    case QtInfoMsg:
        fprintf(stdout, "I: [%s] (%s:%u, %s)\n", context.category, localMsg.constData(), context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stdout, "W: [%s] (%s:%u, %s)\n", context.category, localMsg.constData(), context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stdout, "C: [%s] (%s:%u, %s)\n", context.category, localMsg.constData(), context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stdout, "F: [%s] (%s:%u, %s)\n", context.category, localMsg.constData(), context.line, context.function);
        abort();
    }

    fflush(stdout);
}
