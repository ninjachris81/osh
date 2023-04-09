#include "qmqttcommunicationmanager.h"

#include <QStringListIterator>

#include "qmqttmessageconverter.h"
#include "device/devicediscoverymanagerbase.h"
#include "shared/mqtt_qt.h"
#include "macros.h"

QMqttCommunicationManager::QMqttCommunicationManager(QObject *parent) : MqttCommunicationManagerBase (parent)
{
    connect(&m_mqttClient, &QMqttClient::connected, this, &MqttCommunicationManagerBase::mqttConnected);
    connect(&m_mqttClient, &QMqttClient::disconnected, this, &MqttCommunicationManagerBase::mqttDisconnected);

    connect(&m_mqttClient, &QMqttClient::errorChanged, this, &QMqttCommunicationManager::_onMqttError);
    connect(&m_mqttClient, &QMqttClient::stateChanged, this, &QMqttCommunicationManager::_onMqttStateChanged);

    m_messageConverter.setCommManager(this);
}

void QMqttCommunicationManager::_init(LocalConfig* config) {
    iDebug() << Q_FUNC_INFO;

    REQUIRE_MANAGER(DeviceDiscoveryManagerBase);

    m_mqttClient.setHostname(config->getString(MQTT_HOST, "localhost"));
    m_mqttClient.setPort(static_cast<quint16>(config->getInt(MQTT_PORT, 1883)));
    m_mqttClient.setCleanSession(false);
    m_reconnectTimeoutMs = config->getInt(MQTT_RECONNECT_TIMEOUT, 5000);
}

void QMqttCommunicationManager::_onMqttError(QMqttClient::ClientError error) {
    iWarning() << Q_FUNC_INFO << error;
    QTimer::singleShot(m_reconnectTimeoutMs, [this]() {
        _onTryConnect();
    });
}

void QMqttCommunicationManager::_onMqttStateChanged(QMqttClient::ClientState state) {
    iDebug() << Q_FUNC_INFO << state;
    if (state == QMqttClient::ClientState::Disconnected) {
        QTimer::singleShot(m_reconnectTimeoutMs, [this]() {
            _onTryConnect();
        });
    }
}

void QMqttCommunicationManager::subscribeChannels(QStringList topics) {
    iDebug() << Q_FUNC_INFO << topics;

    QStringListIterator it(topics);
    while(it.hasNext()) {
        QMqttSubscription* sub = m_mqttClient.subscribe(QMqttTopicFilter(buildPath(QStringList() << it.next() << MQTT_WILDCARD).join(MQTT_PATH_SEP)));
        iDebug() << "Subscribed to" << sub->topic().filter();
        m_subscriptions.append(sub);
        connect(sub, &QMqttSubscription::messageReceived, this, &QMqttCommunicationManager::_onMqttMsgReceived);
    }
}

void QMqttCommunicationManager::subscribeControllerChannels(QStringList controllers) {
    iDebug() << Q_FUNC_INFO << controllers;

    QStringListIterator it(controllers);
    while(it.hasNext()) {
        QMqttSubscription* sub = m_mqttClient.subscribe(QMqttTopicFilter(buildPath(QStringList() << MQTT_MESSAGE_TYPE_CO << it.next()).join(MQTT_PATH_SEP)));
        iDebug() << "Subscribed to controller" << sub->topic().filter();
        m_subscriptions.append(sub);
        connect(sub, &QMqttSubscription::messageReceived, this, &QMqttCommunicationManager::_onMqttMsgReceived);
    }
}

bool QMqttCommunicationManager::_sendMessage(MessageBase &message) {
    iDebug() << Q_FUNC_INFO;

    if (m_mqttClient.state()==QMqttClient::Connected) {
        m_mqttClient.publish(m_messageConverter.getTopicName(message), MqttCommunicationManagerBase::serializePayload(message), 0, MqttCommunicationManagerBase::isRetainedMessage(message));
        return true;
    } else {
        iWarning() << "Cannot publish" << m_mqttClient.state();
        return false;
    }
}

void QMqttCommunicationManager::_onMqttMsgReceived(QMqttMessage message) {
    iDebug() << Q_FUNC_INFO << message.topic() << message.payload();

    MessageBase* msg = m_messageConverter.getMessage(message);
    if (msg != nullptr) {
        handleReceivedMessage(msg);
        msg->deleteLater();
    } else {
        //iWarning() << "Received invalid message" << message.topic();
    }
}

void QMqttCommunicationManager::_startConnect() {
    _onTryConnect();
}

void QMqttCommunicationManager::_onTryConnect() {
    iDebug() << Q_FUNC_INFO << m_mqttClient.hostname() << m_mqttClient.port();

    if (m_mqttClient.state() != QMqttClient::Connected) {
        m_mqttClient.setClientId(getManager<DeviceDiscoveryManagerBase>(DeviceDiscoveryManagerBase::MANAGER_ID)->device()->fullId());
        m_mqttClient.connectToHost();
    } else {
        iWarning() << "Already connected";
    }
}
