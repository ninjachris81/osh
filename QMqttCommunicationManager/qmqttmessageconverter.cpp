#include "qmqttmessageconverter.h"

#include "communication/mqtt/mqttcommunicationmanagerbase.h"

#include "qmqttcommunicationmanager.h"

#include "shared/mqtt_qt.h"

QMqttMessageConverter::QMqttMessageConverter(QObject *parent) : QObject(parent)
{
}

MessageBase* QMqttMessageConverter::getMessage(QMqttMessage &message) {
    return m_commManager->getMessage(message.topic().levels(), message.payload(), message.retain());
}

QMqttTopicName QMqttMessageConverter::getTopicName(MessageBase &message) {
    QStringList path = m_commManager->getTopicName(message);
    return QMqttTopicName(path.join(MQTT_PATH_SEP));
}

void QMqttMessageConverter::setCommManager(QMqttCommunicationManager* commManager) {
    m_commManager = commManager;
}
