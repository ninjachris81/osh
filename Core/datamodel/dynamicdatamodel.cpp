#include "dynamicdatamodel.h"

#include <QDataStream>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "actor/audioplaybackactor.h"
#include "value/valuegroup.h"

//#include "processor/server/nativeprocessortask.h"

#ifdef PROCESSOR_JS_SUPPORT
    #include "processor/server/jsprocessortask.h"
#endif

DynamicDatamodel::DynamicDatamodel(QObject *parent) : DatamodelBase("DynamicDatamodel", parent)
{
}

void DynamicDatamodel::addActor(QString typeName, ValueGroup *valueGroup, QString id, QVariantMap properties) {
    ActorBase* actor;

    if (typeName == "DigitalActor") {
        actor = addDigitalActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()),
                        properties.value(ActorBase::PROPERTY_IS_ASYNC).toBool());
    } else if (typeName == "ShutterActor") {
        actor = addShutterActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()),
                        properties.value(ShutterActor::PROPERTY_TILT_SUPPORT).toBool(), properties.value(ShutterActor::PROPERTY_FULL_CLOSE_DURATION).toInt(), properties.value(ShutterActor::PROPERTY_FULL_TILT_DURATION).toInt());
    } else if (typeName == "TimerActor") {
        actor = addTimerActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "ToggleActor") {
        actor = addToggleActor(valueGroup, id);
    } else if (typeName == "ValueActor") {
        actor = addValueActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()), static_cast<QVariant::Type>(properties.value(ValueBase::PROPERTY_TYPE_HINT).toInt()));
    } else if (typeName == "AudioPlaybackActor") {
        actor = addAudioPlaybackActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_DEVICE_IDS).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_ACTIVATION_RELAY_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_VOLUME).toFloat(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_VOLUME_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_URL).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_URL_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_CURRENT_TITLE_ID).toString(), properties.value(AudioPlaybackActor::PROPERTY_AUDIO_NAME).toString());
    } else if (typeName == "DoorActor") {
        actor = addDoorActor(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
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
        val = addBooleanValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "IntegerValue") {
        val = addIntegerValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "LongValue") {
        val = addLongValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "DoubleValue") {
        val = addDoubleValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "StringValue") {
        val = addStringValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()));
    } else if (typeName == "EnumValue") {
        val = addEnumValue(valueGroup, id, static_cast<VALUE_TYPE>(properties.value(ValueBase::PROPERTY_VALUE_TYPE).toInt()), static_cast<ValueBase::VALUE_TIMEOUT>(properties.value(ValueBase::PROPERTY_VALUE_TIMEOUT).toInt()), properties.value(EnumValue::PROPERTY_ENUM_COUNT).toInt());
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
