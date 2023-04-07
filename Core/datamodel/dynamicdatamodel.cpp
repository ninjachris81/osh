#include "dynamicdatamodel.h"

#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "value/booleanvalue.h"
#include "value/doublevalue.h"
#include "value/integervalue.h"
#include "value/longvalue.h"
#include "value/stringvalue.h"
#include "actor/digitalactor.h"
#include "actor/audioplaybackactor.h"
#include "value/valuegroup.h"

//#include "processor/server/nativeprocessortask.h"

#ifdef PROCESSOR_JS_SUPPORT
    #include "processor/server/jsprocessortask.h"
#endif

DynamicDatamodel::DynamicDatamodel(QObject *parent) : DatamodelBase("DynamicDatamodel", parent)
{
}

QByteArray DynamicDatamodel::serialize() {
    QJsonObject rootObj;

    serializeMap(rootObj, "knownDevices", m_knownDevices);
    serializeMap(rootObj, "valueGroups", m_valueGroups);
    serializeMap(rootObj, "values", m_values);
    serializeMap(rootObj, "actors", m_actors);
    serializeMap(rootObj, "knownRooms", m_knownRooms);
    serializeMap(rootObj, "processorTasks", m_processorTasks);

    QJsonDocument doc(rootObj);
    return doc.toJson();
}

template <typename K, typename T> void DynamicDatamodel::serializeMap(QJsonObject &obj, QString name, QMap<K, T> map) {
    QJsonArray arr;
    for (SerializationSupport* item : map) {
        QJsonObject obj;
        item->serialize(obj);
        arr.append(obj);
    }
    obj.insert(name, arr);
}

void DynamicDatamodel::deserialize(QByteArray data) {
    QJsonDocument doc = QJsonDocument::fromJson(data);

    deserializeMap(doc.object(), "knownDevices", m_knownDevices, [](KnownDevice* newInstance, QJsonObject) { return newInstance->fullId(); });
    deserializeMap(doc.object(), "valueGroups", m_valueGroups, [](ValueGroup* newInstance, QJsonObject) { return newInstance->id(); });

    deserializeMap(doc.object(), "values", m_values, [this](ValueBase* newInstance, QJsonObject obj) {
        QString valueGroupId = obj.value("valueGroupId").toString();

        if (m_valueGroups.contains(valueGroupId)) {
            newInstance->setValueGroup(m_valueGroups.value(valueGroupId));
        } else {
            iWarning() << "Unable to resolve value group id" << valueGroupId;
        }
        return newInstance->fullId();
    });

    deserializeMap(doc.object(), "actors", m_actors, [this](ActorBase* newInstance, QJsonObject obj) {
        QString valueGroupId = obj.value("valueGroupId").toString();

        if (m_valueGroups.contains(valueGroupId)) {
            newInstance->setValueGroup(m_valueGroups.value(valueGroupId));
        } else {
            iWarning() << "Unable to resolve value group id" << valueGroupId;
        }

        return newInstance->fullId();
    });

    deserializeMap(doc.object(), "knownRooms", m_knownRooms, [this](KnownRoom* newInstance, QJsonObject obj) {
        QJsonArray values = obj.value("values").toArray();
        for (int i=0;i<values.size();i++) {
            QString valueFullId = values.at(i).toString();
            if (m_values.contains(valueFullId)) {
                newInstance->addValue(m_values.value(valueFullId));
            } else {
                iWarning() << "Unable to find value id" << valueFullId;
            }
        }

        QJsonArray actors = obj.value("actors").toArray();
        for (int i=0;i<actors.size();i++) {
            QString actorFullId = actors.at(i).toString();
            if (m_actors.contains(actorFullId)) {
                newInstance->addActor(m_actors.value(actorFullId));
            } else {
                iWarning() << "Unable to find actor id" << actorFullId;
            }
        }

        return newInstance->id();
    });

    //deserializeMap(doc.object(), "processorTasks", m_processorTasks, [](NativeProcessorTask* newInstance, QJsonObject) { return newInstance->id(); });
}

template <typename K, typename T, typename SETUP_FUNC> void DynamicDatamodel::deserializeMap(QJsonObject obj, QString name, QMap<K, T> &map, SETUP_FUNC setupFunc) {
    QJsonArray arr = obj.value(name).toArray();

    for (int i = 0;i<arr.size();i++) {
        QJsonObject dataObj = arr.at(i).toObject();
        QString classType = dataObj.value(SerializableIdentifyable::PROPERTY_CLASSTYPE).toString();

        SerializationSupport* newInstance = nullptr;
        if (classType == KnownDevice::staticMetaObject.className()) {
            newInstance =  new KnownDevice();
        } else if (classType == ValueGroup::staticMetaObject.className()) {
            newInstance = new ValueGroup();

        // values
        } else if (classType == BooleanValue::staticMetaObject.className()) {
            newInstance = new BooleanValue();
        } else if (classType == DoubleValue::staticMetaObject.className()) {
            newInstance = new DoubleValue();
        } else if (classType == IntegerValue::staticMetaObject.className()) {
            newInstance = new IntegerValue();
        } else if (classType == LongValue::staticMetaObject.className()) {
            newInstance = new LongValue();
        } else if (classType == StringValue::staticMetaObject.className()) {
            newInstance = new StringValue();

        // actors
        } else if (classType == DigitalActor::staticMetaObject.className()) {
            newInstance = new DigitalActor();
        } else if (classType == AudioPlaybackActor::staticMetaObject.className()) {
            newInstance = new AudioPlaybackActor();

        } else if (classType == KnownRoom::staticMetaObject.className()) {
            newInstance = new KnownRoom();
            /*
        } else if (classType == NativeProcessorTask::staticMetaObject.className()) {
            newInstance = new NativeProcessorTask();
            */
        } else {
            qFatal("Unsupported class type");
        }

        newInstance->deserialize(arr.at(i).toObject());
        //QString id = setupFunc((T)newInstance, dataObj);
        QString id = "TBD";
        map.insert(id, (T)newInstance);
    }
}

void DynamicDatamodel::addActor(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties) {
    ActorBase* actor;

    if (typeName == "DigitalActor") {
        actor = addDigitalActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(DigitalActor::PROPERTY_VALUE_TIMEOUT).toInt()),
                        properties.value(DigitalActor::PROPERTY_IS_ASYNC).toBool());
    } else if (typeName == "ShutterActor") {
        actor =addShutterActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(DigitalActor::PROPERTY_VALUE_TIMEOUT).toInt()),
                        properties.value(ShutterActor::PROPERTY_TILT_SUPPORT).toBool(), properties.value(ShutterActor::PROPERTY_FULL_CLOSE_DURATION).toInt(), properties.value(ShutterActor::PROPERTY_FULL_TILT_DURATION).toInt());
    } else if (typeName == "ToggleActor") {
        actor = addToggleActor(valueGroup, id);
    } else if (typeName == "ValueActor") {
        actor = addValueActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(DigitalActor::PROPERTY_VALUE_TIMEOUT).toInt()), static_cast<QVariant::Type>(properties.value(ValueBase::PROPERTY_TYPE_HINT).toInt()));
    } else if (typeName == "AudioPlaybackActor") {
        actor = addAudioPlaybackActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(DigitalActor::PROPERTY_VALUE_TIMEOUT).toInt()), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_DEVICE_IDS).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_ACTIVATION_RELAY_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_VOLUME).toFloat(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_VOLUME_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_URL).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_URL_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_CURRENT_TITLE_ID).toString());
    } else if (typeName == "DoorActor") {
        actor = addDoorActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(DigitalActor::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else {
        iWarning() << "Unsupported type name" << typeName;
    }

    if (properties.contains(ActorBase::PROPERTY_PRIORITY)) {
        actor->withPriority(properties.value(ActorBase::PROPERTY_PRIORITY).toInt());
    }
}

void DynamicDatamodel::addValue(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties) {
    ValueBase* val;

    if (typeName == "BooleanValue") {
        val = addBooleanValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "IntegerValue") {
        val = addIntegerValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "LongValue") {
        val = addLongValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "DoubleValue") {
        val = addDoubleValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "StringValue") {
        val = addStringValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "EnumValue") {
        val = addEnumValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(DigitalActor::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()), properties.value(EnumValue::PROPERTY_ENUM_COUNT).toInt());
    } else {
        iWarning() << "Unknown value type" << typeName;
    }

    if (properties.contains(ValueBase::PROPERTY_ALWAYS_EMIT)) {
        val->withAlwaysEmit(properties.value(ValueBase::PROPERTY_ALWAYS_EMIT).toBool());
    }
    if (properties.contains(ValueBase::PROPERTY_PERSIST)) {
        val->withPersist(properties.value(ValueBase::PROPERTY_PERSIST).toBool());
    }
}
