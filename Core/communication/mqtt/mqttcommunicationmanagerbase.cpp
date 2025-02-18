#include "mqttcommunicationmanagerbase.h"

#include <QDebug>
#include <QMetaEnum>

#include "shared/mqtt_qt.h"
#include "value/valuemessage.h"
#include "device/devicediscoverymessage.h"
#include "time/systemtimemessage.h"
#include "warn/systemwarningmessage.h"
#include "actor/actormessage.h"
#include "controller/controllermessage.h"
#include "controller/controllermanager.h"
#include "log/logmessage.h"
#include "processor/scriptresultmessage.h"
#include "doorunlock/doorunlockmessage.h"
#include "log/logmanager.h"

MqttCommunicationManagerBase::MqttCommunicationManagerBase(QObject *parent) : CommunicationManagerBase(parent)
{
    connect(this, &MqttCommunicationManagerBase::mqttConnected, this, &MqttCommunicationManagerBase::onMqttConnected);
    connect(this, &MqttCommunicationManagerBase::mqttDisconnected, this, &MqttCommunicationManagerBase::onMqttDisconnected);
    connect(this, &MqttCommunicationManagerBase::mqttConnected, this, &CommunicationManagerBase::connected);
    connect(this, &MqttCommunicationManagerBase::mqttDisconnected, this, &CommunicationManagerBase::disconnected);

    registerMessageType(MessageBase::MESSAGE_TYPE_VALUE, true, MQTT_MESSAGE_TYPE_VA, 2, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_ACTOR, false, MQTT_MESSAGE_TYPE_AC, 2, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY, false, MQTT_MESSAGE_TYPE_DD, 2, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_SYSTEM_TIME, false, MQTT_MESSAGE_TYPE_ST, 0, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_SYSTEM_WARNING, false, MQTT_MESSAGE_TYPE_SW, 1, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_CONTROLLER, false, MQTT_MESSAGE_TYPE_CO, 1, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_LOG, false, MQTT_MESSAGE_TYPE_LO, 2, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_SCRIPT_RESULT, false, MQTT_MESSAGE_TYPE_SR, 1, true);
    registerMessageType(MessageBase::MESSAGE_TYPE_DOOR_UNLOCK, false, MQTT_MESSAGE_TYPE_DU, 2, true);

    QMetaEnum e = QMetaEnum::fromType<MessageBase::MESSAGE_TYPE>();
    iDebug() << "Checking message types" << e.keyCount()-1 << m_messageTypes.count();
    Q_ASSERT(e.keyCount()-1 == m_messageTypes.count());        // -1 because of UNKNOWN
}

void MqttCommunicationManagerBase::registerMessageType(MessageBase::MESSAGE_TYPE messageType, bool isRetained, QString mqttTypePath, quint8 mqttPathLevels, bool dropOwnMessages) {
    MessageTypeInfo info;

    info.isRetained = isRetained;
    info.mqttTypePath = mqttTypePath;
    info.mqttPathLevels = mqttPathLevels;
    info.dropOwnMessages = dropOwnMessages;

    m_messageTypes.insert(messageType, info);
}

MessageBase* MqttCommunicationManagerBase::getMessage(QStringList levels, QByteArray payload, bool isRetain) {
    iDebug() << Q_FUNC_INFO << levels << payload << isRetain;

    QStringList path = MqttCommunicationManagerBase::removeBasePath(levels);
    QStringList firstLevelPath = MqttCommunicationManagerBase::removeMessageTypePath(path);
    MessageBase::MESSAGE_TYPE messageType = getMessageType(path.first());
    MessageTypeInfo info = m_messageTypes.value(messageType);
    if (isRetain && !info.isRetained) {
        iWarning() << "Ignoring retained message" << messageType;
        return nullptr;
    }

    if (info.mqttPathLevels == firstLevelPath.size()) {
        QVariantMap value = parseJSONPayload(payload);

        QString senderDeviceId;
        if (!isRetain && value.contains(MQTT_SENDER_DEVICE_ID_ATTR)) {
            senderDeviceId = value.value(MQTT_SENDER_DEVICE_ID_ATTR, "").toString();

            if (info.dropOwnMessages && senderDeviceId == deviceId()) {
                iDebug() << "Dropping own message" << messageType;
                return nullptr;
            }
        }
        qint64 ts;
        if (value.contains(MQTT_TS)) {
            ts = value.value(MQTT_TS, 0).toLongLong();
        }

        MessageBase* msg;

        iDebug() << Q_FUNC_INFO << messageType << value << firstLevelPath;

        switch (messageType) {
        case MessageBase::MESSAGE_TYPE_VALUE: {
            msg = new ValueMessage(firstLevelPath.first(), firstLevelPath.at(1), value);
            break;
        }
        case MessageBase::MESSAGE_TYPE_ACTOR: {
            QVariant actorVal = value.value(MQTT_SINGLE_VALUE_ATTR);
            QVariant actorCmd = value.value(MQTT_ACTOR_CMD_ATTR);

            if (actorCmd.isValid() && actorCmd.canConvert(QVariant::Int)) {
                msg = new ActorMessage(firstLevelPath.first(), firstLevelPath.at(1), actorVal, static_cast<ACTOR_CMDS>(actorCmd.toInt()));
                break;
            } else {
                iWarning() << "Invalid payload value" << value << messageType;
                return nullptr;
            }
        }
        case MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY: {
            QVariant ddVal = value.value(MQTT_SINGLE_VALUE_ATTR);
            QVariant healthVal = value.value(MQTT_HEALTH_STATE_ATTR);
            if (ddVal.isValid() && ddVal.canConvert(QVariant::ULongLong)) {
                DeviceDiscoveryMessage::DeviceHealthState healthState = DeviceDiscoveryMessage::Unknown;

                if (healthVal.isValid() && healthVal.canConvert(QVariant::UInt)) {
                    healthState = static_cast<DeviceDiscoveryMessage::DeviceHealthState>(healthVal.toUInt());
                }

                msg = new DeviceDiscoveryMessage(firstLevelPath.first(), firstLevelPath.at(1), ddVal.toULongLong(), healthState);
                break;
            } else {
                iWarning() << "Invalid payload value" << value << messageType;
                return nullptr;
            }
        }
        case MessageBase::MESSAGE_TYPE_SYSTEM_TIME: {
            QVariant timeVal = parseSingleValue(value);
            if (timeVal.isValid() && timeVal.canConvert(QVariant::LongLong)) {
                msg = new SystemtimeMessage(timeVal.toLongLong());
                break;
            } else {
                iWarning() << "Invalid payload value" << value << messageType;
                return nullptr;
            }
        }
        case MessageBase::MESSAGE_TYPE_SYSTEM_WARNING: {
            QVariant swVal = parseSingleValue(value);
            if (swVal.isValid() && swVal.canConvert(QVariant::String)) {
                msg = new SystemWarningMessage(firstLevelPath.first(), swVal.toString());
                break;
            } else {
                iWarning() << "Invalid payload value" << value << messageType;
                return nullptr;
            }
        }
        case MessageBase::MESSAGE_TYPE_CONTROLLER: {
            msg = new ControllerMessage(firstLevelPath.first(), value);
            break;
        }
        case MessageBase::MESSAGE_TYPE_LOG: {
            QVariant logVal = parseSingleValue(value);
            if (logVal.isValid() && logVal.canConvert(QVariant::String)) {
                msg = new LogMessage(firstLevelPath.first(), LogManager::stringToMsgType(firstLevelPath.at(1)), logVal.toString());
                break;
            } else {
                iWarning() << "Invalid payload value" << value << messageType;
                return nullptr;
            }
        }
        case MessageBase::MESSAGE_TYPE_SCRIPT_RESULT: {
            msg = new ScriptResultMessage(firstLevelPath.first(), value);
            break;
        }
        case MessageBase::MESSAGE_TYPE_DOOR_UNLOCK: {
            msg =  new DoorUnlockMessage(firstLevelPath.first(), firstLevelPath.at(1), value);
            break;
        }
        default:
            iWarning() << "Unknown message type" << levels;
            return nullptr;
        }

        msg->setSenderDeviceId(senderDeviceId);
        msg->setTs(ts);

        return msg;
    } else {
        iWarning() << "Invalid path levels" << firstLevelPath.size() << "expected" << info.mqttPathLevels;
        return nullptr;
    }
}

QStringList MqttCommunicationManagerBase::buildPath(QStringList paths, bool addWildcard) {
    //iDebug() << Q_FUNC_INFO << paths;

    if (paths.first()!=MQTT_BASE_PATH) paths.prepend(MQTT_BASE_PATH);

    if (addWildcard) {
        paths.append(MQTT_WILDCARD);
    //} else if (index>-1){
    //    paths.append(QString::number(index));
    }
    return paths;
}

void MqttCommunicationManagerBase::onMqttConnected() {
    iDebug() << Q_FUNC_INFO;

    if (m_hasCustomChannels) {
        QStringList customChannels;
        customChannels << m_customChannels;
        customChannels << m_customValueGroupChannels;
        customChannels << m_customActorGroupChannels;

        subscribeChannels(customChannels);
    } else {
        switch(managerRegistration()->instanceRole()) {
        case ManagerRegistration::SERVER:
            subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_DD << MQTT_MESSAGE_TYPE_SW << MQTT_MESSAGE_TYPE_AC);
            break;
        case ManagerRegistration::CLIENT:
            subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);
            break;
        case ManagerRegistration::GUI:
            subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_DD << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_SW << MQTT_MESSAGE_TYPE_AC << MQTT_MESSAGE_TYPE_SR << MQTT_MESSAGE_TYPE_LO);
            break;
        default:
            iWarning() << "Unsupported instance role";
            break;
        }
    }

    ControllerManager* controllerManager = getManager<ControllerManager>(ControllerManager::MANAGER_ID);
    subscribeControllerChannels(controllerManager->controllerNames());
}

void MqttCommunicationManagerBase::onMqttDisconnected() {
    iWarning() << Q_FUNC_INFO;


}

/*
QVariant MqttCommunicationManagerBase::parseCompactPayload(char typeId, QByteArray payload) {
    switch(typeId) {
    case MQTT_ID_DOUBLE:
        return QByteArray(payload).toDouble();
    case MQTT_ID_INTEGER:
        return QByteArray(payload).toInt();
    case MQTT_ID_LONG:
        return QByteArray(payload).toLongLong();
    case MQTT_ID_STRING:
        return QString(QByteArray((payload)));
    case MQTT_ID_BOOL:
        return QByteArray(payload).toInt()==1;
    case MQTT_ID_INVALID:
        return QVariant();
    default:
        iWarning() << "Invalid type id" << typeId;
        return QVariant();
    }
}
*/

QVariantMap MqttCommunicationManagerBase::parseJSONPayload(QByteArray payload) {
    QJsonDocument doc = QJsonDocument::fromJson(payload);
    if (doc.isEmpty() || doc.isNull()) {
        // ok, empty
    } else if (doc.isObject()) {
        return doc.object().toVariantMap();
    } else {
        iWarning() << "Invalid payload" << payload;
    }

    return QVariantMap();
}

QVariant MqttCommunicationManagerBase::parseSingleValue(QVariantMap value) {
    if (value.contains(MQTT_SINGLE_VALUE_ATTR)) {
        return value.value(MQTT_SINGLE_VALUE_ATTR);
    } else {
        iWarning() << "value attribute missing";
        return QVariant();
    }
}

QByteArray MqttCommunicationManagerBase::serializePayload(MessageBase &message) {
    iDebug() << Q_FUNC_INFO << message.getMessageType();

    switch(message.getMessageType()) {
    case MessageBase::MESSAGE_TYPE_VALUE: {
        ValueMessage* valueMessage = static_cast<ValueMessage*>(&message);
        return serializeSingleJSONValue(valueMessage->rawValue());
    }
    case MessageBase::MESSAGE_TYPE_ACTOR: {
        ActorMessage* actorMessage = static_cast<ActorMessage*>(&message);
        QVariantMap map;
        if (actorMessage->rawValue().isValid()) {
            map.insert(MQTT_SINGLE_VALUE_ATTR, actorMessage->rawValue());
        }
        map.insert(MQTT_ACTOR_CMD_ATTR, actorMessage->cmd());
        return serializeJSONValue(map);
    }
    case MessageBase::MESSAGE_TYPE_SYSTEM_TIME: {
        SystemtimeMessage* systimeMessage = static_cast<SystemtimeMessage*>(&message);
        return serializeSingleJSONValue(systimeMessage->ts());
    }
    case MessageBase::MESSAGE_TYPE_SYSTEM_WARNING: {
        SystemWarningMessage* syswarnMessage = static_cast<SystemWarningMessage*>(&message);
        return serializeSingleJSONValue(syswarnMessage->msg());
    }
    case MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY: {
        DeviceDiscoveryMessage* ddMessage = static_cast<DeviceDiscoveryMessage*>(&message);
        QVariantMap map;
        map.insert(MQTT_SINGLE_VALUE_ATTR, ddMessage->upTime());
        map.insert(MQTT_HEALTH_STATE_ATTR, ddMessage->healthState());
        return serializeJSONValue(map);
    }
    case MessageBase::MESSAGE_TYPE_CONTROLLER: {
        ControllerMessage* controllerMessage = static_cast<ControllerMessage*>(&message);
        return serializeSingleJSONValue(controllerMessage->data());
    }
    case MessageBase::MESSAGE_TYPE_LOG: {
        LogMessage* logMessage = static_cast<LogMessage*>(&message);
        return serializeSingleJSONValue(logMessage->message().toUtf8());
    }
    case MessageBase::MESSAGE_TYPE_SCRIPT_RESULT: {
        ScriptResultMessage* scriptResultMessage = static_cast<ScriptResultMessage*>(&message);
        return serializeSingleJSONValue(scriptResultMessage->value());
    }
    case MessageBase::MESSAGE_TYPE_DOOR_UNLOCK: {
        DoorUnlockMessage* doorUnlockMessage = static_cast<DoorUnlockMessage*>(&message);
        return serializeJSONValue(doorUnlockMessage->values());
    }
    default:
        iWarning() << "Unknown message type" << message.getMessageType();
        return nullptr;
    }
}

QByteArray MqttCommunicationManagerBase::serializeJSONValue(QVariantMap mapData) {
    mapData.insert(MQTT_SENDER_DEVICE_ID_ATTR, deviceId());
    mapData.insert(MQTT_TS, QDateTime::currentMSecsSinceEpoch());
    return QJsonDocument::fromVariant(mapData).toJson(QJsonDocument::Compact);
}

QByteArray MqttCommunicationManagerBase::serializeSingleJSONValue(QVariant value) {
    QVariantMap mapData;
    mapData.insert(MQTT_SINGLE_VALUE_ATTR, value);
    return serializeJSONValue(mapData);
}

/*
QByteArray MqttCommunicationManagerBase::serializeCompactValue(QVariant value) {
    iDebug() << Q_FUNC_INFO << value;

    QByteArray returnData;

    if (value.isValid()) {
        if (value.type()==QVariant::Double) {
            returnData.append(MQTT_ID_DOUBLE);
            returnData.append(QByteArray::number(value.toDouble()));
        } else if (value.type()==QVariant::Int) {
            returnData.append(MQTT_ID_INTEGER);
            returnData.append(QByteArray::number(value.toInt()));
        } else if (value.type()==QVariant::LongLong) {
            returnData.append(MQTT_ID_LONG);
            returnData.append(QByteArray::number(value.toLongLong()));
        } else if (value.type()==QVariant::String) {
            returnData.append(MQTT_ID_STRING);
            returnData.append(value.toString());
        } else if (value.type()==QVariant::Bool) {
            returnData.append(MQTT_ID_BOOL);
            returnData.append(value.toBool()?"1":"0");
        } else {
            iWarning() << "Cannot serialize" << value.typeName();
        }
    } else {
        returnData.append(MQTT_ID_INVALID);
        returnData.append(MQTT_INVALID_PAYLOAD);
    }

    iDebug() << "Payload" << returnData;
    return returnData;
}
*/

QStringList MqttCommunicationManagerBase::getTopicName(MessageBase &message) {
    QStringList path;
    path << MQTT_BASE_PATH;

    MessageTypeInfo info = m_messageTypes.value(message.getMessageType());
    path << info.mqttTypePath;

    if (!message.getFirstLevelId().isEmpty()) {
        path << message.getFirstLevelId();
    }

    if (!message.getSecondLevelId().isEmpty()) {
        path << message.getSecondLevelId();
    }

    return path;
}

MessageBase::MESSAGE_TYPE MqttCommunicationManagerBase::getMessageType(QString name) {
    QMapIterator<MessageBase::MESSAGE_TYPE, MessageTypeInfo> it(m_messageTypes);

    while(it.hasNext()) {
        it.next();
        if (it.value().mqttTypePath == name) {
            return it.key();
        }
    }

    iWarning() << "Unknown message type" << name;
    return MessageBase::MESSAGE_TYPE_UNKNOWN;
}

QStringList MqttCommunicationManagerBase::removeBasePath(QStringList paths) {
    if (paths.first()==MQTT_BASE_PATH) paths.removeFirst();
    return paths;
}

QStringList MqttCommunicationManagerBase::removeMessageTypePath(QStringList paths) {
    QMapIterator<MessageBase::MESSAGE_TYPE, MessageTypeInfo> it(m_messageTypes);

    while(it.hasNext()) {
        it.next();
        if (paths.first()==it.value().mqttTypePath) {
            paths.removeFirst();
            break;
        }
    }

    return paths;
}

bool MqttCommunicationManagerBase::isRetainedMessage(MessageBase &message) {
    MessageTypeInfo info = m_messageTypes.value(message.getMessageType());
    return info.isRetained;
}

void MqttCommunicationManagerBase::setCustomChannels(QStringList customChannels) {
    m_customChannels = customChannels;
    m_hasCustomChannels = true;
}

void MqttCommunicationManagerBase::setCustomValueGroups(QStringList customValueGroupChannels) {
    for (QString c : customValueGroupChannels) {
        m_customValueGroupChannels << (QString(MQTT_MESSAGE_TYPE_VA) + QString(MQTT_PATH_SEP) + c);
    }

    m_hasCustomChannels = true;
}

void MqttCommunicationManagerBase::setCustomActorValueGroups(QStringList customActorGroupChannels) {
    for (QString c : customActorGroupChannels) {
        m_customActorGroupChannels << (QString(MQTT_MESSAGE_TYPE_AC) + QString(MQTT_PATH_SEP) + c);
    }

    m_hasCustomChannels = true;
}

