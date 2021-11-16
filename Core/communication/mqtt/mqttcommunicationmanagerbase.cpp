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

MqttCommunicationManagerBase::MqttCommunicationManagerBase(QObject *parent) : CommunicationManagerBase(parent)
{
    connect(this, &MqttCommunicationManagerBase::mqttConnected, this, &MqttCommunicationManagerBase::onMqttConnected);
    connect(this, &MqttCommunicationManagerBase::mqttDisconnected, this, &MqttCommunicationManagerBase::onMqttDisconnected);
    connect(this, &MqttCommunicationManagerBase::mqttConnected, this, &CommunicationManagerBase::connected);
    connect(this, &MqttCommunicationManagerBase::mqttDisconnected, this, &CommunicationManagerBase::disconnected);

    registerMessageType(MessageBase::MESSAGE_TYPE_VALUE, true, COMPACT, MQTT_MESSAGE_TYPE_VA, 2);
    registerMessageType(MessageBase::MESSAGE_TYPE_ACTOR, true, COMPACT, MQTT_MESSAGE_TYPE_AC, 2);
    registerMessageType(MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY, false, NONE, MQTT_MESSAGE_TYPE_DD, 1);
    registerMessageType(MessageBase::MESSAGE_TYPE_SYSTEM_TIME, false, COMPACT, MQTT_MESSAGE_TYPE_ST, 0);
    registerMessageType(MessageBase::MESSAGE_TYPE_SYSTEM_WARNING, false, COMPACT, MQTT_MESSAGE_TYPE_SW, 1);
    registerMessageType(MessageBase::MESSAGE_TYPE_CONTROLLER, false, JSON, MQTT_MESSAGE_TYPE_CO, 1);
    registerMessageType(MessageBase::MESSAGE_TYPE_LOG, false, TEXT_UTF8, MQTT_MESSAGE_TYPE_LO, 1);

    QMetaEnum e = QMetaEnum::fromType<MessageBase::MESSAGE_TYPE>();
    iDebug() << "Checking message types" << e.keyCount()-1 << m_messageTypes.count();
    Q_ASSERT(e.keyCount()-1 == m_messageTypes.count());        // -1 because of UNKNOWN
}

void MqttCommunicationManagerBase::registerMessageType(MessageBase::MESSAGE_TYPE messageType, bool isRetained, ParsingType parsingType, QString mqttTypePath, quint8 mqttPathLevels) {
    MessageTypeInfo info;

    info.isRetained = isRetained;
    info.parsingType = parsingType;
    info.mqttTypePath = mqttTypePath;
    info.mqttPathLevels = mqttPathLevels;

    m_messageTypes.insert(messageType, info);
}

MessageBase* MqttCommunicationManagerBase::getMessage(QStringList levels, QByteArray payload) {
    iDebug() << Q_FUNC_INFO << levels << payload;

    QStringList path = MqttCommunicationManagerBase::removeBasePath(levels);
    QStringList firstLevelPath = MqttCommunicationManagerBase::removeMessageTypePath(path);
    MessageBase::MESSAGE_TYPE messageType = getMessageType(path.first());
    MessageTypeInfo info = m_messageTypes.value(messageType);

    if (info.mqttPathLevels == firstLevelPath.size()) {
        QVariant rawValue = parsePayload(messageType, payload);

        iDebug() << Q_FUNC_INFO << messageType << rawValue << firstLevelPath;

        switch (messageType) {
        case MessageBase::MESSAGE_TYPE_VALUE: {
            return new ValueMessage(firstLevelPath.first(), firstLevelPath.at(1), rawValue);
        }
        case MessageBase::MESSAGE_TYPE_ACTOR: {
            return new ActorMessage(firstLevelPath.first(), firstLevelPath.at(1), static_cast<ACTOR_CMDS>(rawValue.toInt()));
        }
        case MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY: {
            return new DeviceDiscoveryMessage(firstLevelPath.first());
        }
        case MessageBase::MESSAGE_TYPE_SYSTEM_TIME: {
            return new SystemtimeMessage(rawValue.toLongLong());
        }
        case MessageBase::MESSAGE_TYPE_SYSTEM_WARNING: {
            return new SystemWarningMessage(firstLevelPath.first(), rawValue.toString());
        }
        case MessageBase::MESSAGE_TYPE_CONTROLLER: {
            return new ControllerMessage(firstLevelPath.first(), rawValue);
        }
        case MessageBase::MESSAGE_TYPE_LOG: {
            return new LogMessage(firstLevelPath.first(), rawValue.toString());
        }
        default:
            iWarning() << "Unknown message type" << levels;
            return nullptr;
        }
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

    switch(managerRegistration()->instanceRole()) {
    case ManagerRegistration::SERVER:
        subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_DD << MQTT_MESSAGE_TYPE_SW << MQTT_MESSAGE_TYPE_AC);
        break;
    case ManagerRegistration::CLIENT:
        subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_AC);
        break;
    case ManagerRegistration::GUI:
        subscribeChannels(QStringList() << MQTT_MESSAGE_TYPE_VA << MQTT_MESSAGE_TYPE_DD << MQTT_MESSAGE_TYPE_ST << MQTT_MESSAGE_TYPE_SW << MQTT_MESSAGE_TYPE_AC);
        break;
    default:
        iWarning() << "Unsupported instance role";
        break;
    }

    ControllerManager* controllerManager = getManager<ControllerManager>(ControllerManager::MANAGER_ID);
    subscribeControllerChannels(controllerManager->controllerNames());
}

void MqttCommunicationManagerBase::onMqttDisconnected() {

}

QVariant MqttCommunicationManagerBase::parsePayload(MessageBase::MESSAGE_TYPE messageType, QByteArray payload) {
    MessageTypeInfo info = m_messageTypes.value(messageType);

    switch(info.parsingType) {
    case NONE:
        return QVariant();
    case COMPACT:
        if (payload.count()>=MQTT_MIN_MSG_SIZE) {
            return parseCompactPayload(payload.at(0), payload.mid(1));
        } else {
            iWarning() << "Invalid compact msg size" << payload.size();
            return QVariant();
        }
    case JSON:
        if (!payload.isEmpty()) {
            return parseJSONPayload(payload);
        } else {
            return QVariant();
        }
    case TEXT_UTF8:
        return QString::fromUtf8(payload);
    default:
        iWarning() << "Unknown parsing type" << info.parsingType;
    }

    return QVariant();
}

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

QJsonDocument MqttCommunicationManagerBase::parseJSONPayload(QByteArray payload) {
    return QJsonDocument::fromJson(payload);
}

QByteArray MqttCommunicationManagerBase::serializePayload(MessageBase &message) {
    iDebug() << Q_FUNC_INFO << message.getMessageType();

    switch(message.getMessageType()) {
    case MessageBase::MESSAGE_TYPE_VALUE: {
        ValueMessage* valueMessage = static_cast<ValueMessage*>(&message);
        return serializeCompactValue(valueMessage->rawValue());
    }
    case MessageBase::MESSAGE_TYPE_SYSTEM_TIME: {
        SystemtimeMessage* systimeMessage = static_cast<SystemtimeMessage*>(&message);
        return serializeCompactValue(systimeMessage->ts());
    }
    case MessageBase::MESSAGE_TYPE_SYSTEM_WARNING: {
        SystemWarningMessage* syswarnMessage = static_cast<SystemWarningMessage*>(&message);
        return serializeCompactValue(syswarnMessage->msg());
    }
    case MessageBase::MESSAGE_TYPE_DEVICE_DISCOVERY:
        // TODO
        return QByteArray();
    case MessageBase::MESSAGE_TYPE_CONTROLLER: {
        ControllerMessage* controllerMessage = static_cast<ControllerMessage*>(&message);
        return QJsonDocument::fromVariant(controllerMessage->data()).toJson();
    }
    case MessageBase::MESSAGE_TYPE_LOG: {
        LogMessage* logMessage = static_cast<LogMessage*>(&message);
        return logMessage->message().toUtf8();
    }
    default:
        iWarning() << "Unknown message type" << message.getMessageType();
    }
}

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
