#include "logmanager.h"

#include <QDebug>
#include <QFileInfo>
#include <QDir>

#include "communication/communicationmanagerbase.h"

QLatin1Literal LogManager::MANAGER_ID = QLatin1Literal("LogManager");

LogManager::LogManager(QObject *parent) : ManagerBase(parent)
{
}

void LogManager::init(LocalConfig *config) {
    //qInstallMessageHandler(&LogManager::messageHandler);

    iDebug() << Q_FUNC_INFO;
}

QString LogManager::id() {
    return MANAGER_ID;
}

MessageBase::MESSAGE_TYPE LogManager::getMessageType() {
    return MessageBase::MESSAGE_TYPE_LOG;
}

void LogManager::handleReceivedMessage(MessageBase* msg) {
    iDebug() << Q_FUNC_INFO;
}

void LogManager::registerManager(ManagerBase* manager) {
    m_managers.insert(manager->id(), manager);
}

void LogManager::messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();

    QString loc(context.file);
    QStringList locs = loc.split(QDir::separator());

    switch (type) {
    case QtDebugMsg:
        //fprintf(stdout, "Debug: %s (%s)\n", localMsg.constData(), locs.last().toLatin1().data());
        fprintf(stdout, "D: [%s] %s (%s:%u, %s)\n", context.category, localMsg.constData(), context.file, context.line, context.function);
        /*
        if (strcmp(context.category, QLatin1Literal("default").latin1())==0) {
            fprintf(stdout, "D: %s\n", localMsg.constData());
        } else {
            fprintf(stdout, "D: %s %s\n", context.category, localMsg.constData());
        }*/
        break;
    case QtInfoMsg:
        fprintf(stdout, "I: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "W: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "C: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "F: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}
