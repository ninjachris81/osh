#ifndef QMQTTCOMMUNICATIONMANAGER_H
#define QMQTTCOMMUNICATIONMANAGER_H

#include <QObject>

#include <QtMqtt/QMqttClient>
#include <QtMqtt/QMqttSubscription>

#include "sharedlib.h"

#include "communication/mqtt/mqttcommunicationmanagerbase.h"
#include "config/localconfig.h"
#include "qmqttmessageconverter.h"

#include <QList>

class SHARED_LIB_EXPORT QMqttCommunicationManager : public MqttCommunicationManagerBase
{
    Q_OBJECT

public:
    explicit QMqttCommunicationManager(QObject *parent = nullptr);

private:
    QMqttMessageConverter m_messageConverter;
    QMqttClient m_mqttClient;

    QList<QMqttSubscription*> m_subscriptions;

    quint16 m_reconnectTimeoutMs;

protected:
    /*virtual*/ void _init(LocalConfig *config);
    /*virtual*/ bool _sendMessage(MessageBase &message);
    /*virtual*/ void _startConnect();

    /*virtual*/ void subscribeChannels(QStringList topics);
    /*virtual*/ void subscribeControllerChannels(QStringList controllers);

protected slots:
    void _onTryConnect();
    void _onMqttError(QMqttClient::ClientError error);
    void _onMqttStateChanged(QMqttClient::ClientState state);

    void _onMqttMsgReceived(QMqttMessage msg);

};

#endif // QMQTTCOMMUNICATIONMANAGER_H
