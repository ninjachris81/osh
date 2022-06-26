#ifndef MQTTCOMMUNICATIONMANAGERBASE_H
#define MQTTCOMMUNICATIONMANAGERBASE_H

#include <QObject>
#include <QMap>
#include <QJsonDocument>

#include "communication/communicationmanagerbase.h"

#include "communication/messagebase.h"
#include "value/valuegroup.h"

#define MQTT_HOST "mqtt.host"
#define MQTT_PORT "mqtt.port"

class MqttCommunicationManagerBase : public CommunicationManagerBase
{
    Q_OBJECT
public:
    struct MessageTypeInfo {
        bool isRetained;
        QString mqttTypePath;
        quint8 mqttPathLevels;
    };

    explicit MqttCommunicationManagerBase(QObject *parent = nullptr);

    void registerMessageType(MessageBase::MESSAGE_TYPE messageType, bool isRetained, QString mqttTypePath, quint8 mqttPathLevels);

    MessageBase* getMessage(QStringList levels, QByteArray payload);

    QByteArray serializePayload(MessageBase &message);

    MessageBase::MESSAGE_TYPE getMessageType(QString name);

    QStringList getTopicName(MessageBase &message);

    QStringList removeBasePath(QStringList paths);
    QStringList removeMessageTypePath(QStringList paths);

    bool isRetainedMessage(MessageBase &message);

    void setCustomChannels(QStringList customChannels);

private:
    bool m_hasCustomChannels = false;
    QStringList m_customChannels;
    //QVariant parseCompactPayload(char typeId, QByteArray payload);
    QVariantMap parseJSONPayload(QByteArray payload);
    QVariant parseSingleValue(QVariantMap value);
    //QByteArray serializeCompactValue(QVariant value);
    QByteArray serializeJSONValue(QVariantMap mapData);
    QByteArray serializeSingleJSONValue(QVariant value);

protected:
    QMap<MessageBase::MESSAGE_TYPE, MessageTypeInfo> m_messageTypes;
    QStringList buildPath(QStringList paths, bool addWildcard = false);

    virtual void subscribeChannels(QStringList topics) = 0;
    virtual void subscribeControllerChannels(QStringList controllers) = 0;

protected slots:
    void onMqttConnected();
    void onMqttDisconnected();

signals:
    void mqttConnected();
    void mqttDisconnected();

public slots:
};

#endif // MQTTCOMMUNICATIONMANAGERBASE_H
