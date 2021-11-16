#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include <QObject>
#include <QList>
#include <QLoggingCategory>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "shared/logging_categories_qt.h"

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

    static void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

private:
    QMap<QString, ManagerBase*> m_managers;

signals:

public slots:
};

#endif // LOGMANAGER_H
