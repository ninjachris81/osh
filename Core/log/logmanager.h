#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QList>
#include <QLoggingCategory>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "shared/logging_categories_qt.h"
#include "communication/communicationmanagerbase.h"
#include "device/devicediscoverymanagerbase.h"

class LogManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit LogManager(QObject *parent = nullptr);

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    void registerManager(ManagerBase* manager);

    void publishLog(QtMsgType type, QString msg);

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

    static QString msgTypeToString(QtMsgType type);

    static QtMsgType stringToMsgType(QString type);

    static LogManager* m_instance;

private:
    QMap<QString, ManagerBase*> m_managers;
    CommunicationManagerBase* m_commManager;
    DeviceDiscoveryManagerBase* m_ddManager;

protected:
    QList<QtMsgType> m_typeFilter;

signals:
    void logMessage(QtMsgType type, QString deviceId, QString msg);

public slots:
};

#endif // LOGMANAGER_H
