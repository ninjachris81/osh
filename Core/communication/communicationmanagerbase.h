#ifndef COMMUNICATIONMANAGERBASE_H
#define COMMUNICATIONMANAGERBASE_H

#include <QObject>
#include "sharedlib.h"

#include "manager/managerbase.h"
#include "messagebase.h"
#include "value/valuegroup.h"
#include "config/localconfig.h"

#include <QMap>

#define SEND_ERROR 0

class SHARED_LIB_EXPORT CommunicationManagerBase : public ManagerBase
{
    Q_OBJECT
public:
    explicit CommunicationManagerBase(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    quint64 sendMessage(MessageBase &message);
    /*virtual*/ void init(LocalConfig* config) override;
    /*virtual*/ void postInit() override;

    /*virtual*/ QString id() final;

    /*virtual*/ LogCat::LOGCAT logCat() final;

    bool isConnected();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

protected:
    bool m_isConnected = false;
    virtual void _init(LocalConfig* config) = 0;
    virtual void _startConnect() = 0;
    virtual bool _sendMessage(MessageBase &message) = 0;

signals:
    void connected();
    void disconnected();

    void isConnectedChanged();

private:
    void setIsConnected(bool connected);
    QMap<MessageBase::MESSAGE_TYPE, ManagerBase*> m_managerMessageTypes;


public slots:
};

#endif // COMMUNICATIONMANAGERBASE_H
