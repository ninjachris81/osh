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

#include "processor/server/nativeprocessortask.h"

#ifdef PROCESSOR_JS_SUPPORT
    #include "processor/server/jsprocessortask.h"
#endif

DynamicDatamodel::DynamicDatamodel(QObject *parent) : DatamodelBase("DynamicDatamodel", parent)
{


    /*
     *
     *  FOR TEST
     *
    */

    return;


    // DEVICES
    addKnownDevice("349785676", "CoreServer", "Server");
    addKnownDevice("582645258", "CoreUI", "GUI");
    addKnownDevice("66403375", "InputService", "Node EG Input");
    addKnownDevice("66403375", "RelayService", "Node EG Relay");
    addKnownDevice("0020", "SensorService_20", "Sensor EG Küche");

    // ROOMS
    // BASEMENT
    KnownRoom* heatingRoom = addKnownRoom("heatingRoom", "Heizraum");
    KnownRoom* workshop = addKnownRoom("workshop", "Werkstatt");
    KnownRoom* basementFloor0 = addKnownRoom("basementFloor0", "HF");
    KnownRoom* basementFloor1 = addKnownRoom("basementFloor1", "Flur");
    KnownRoom* storage1 = addKnownRoom("storage1", "L1");
    KnownRoom* storage2 = addKnownRoom("storage2", "L2");
    KnownRoom* storage3 = addKnownRoom("storage3", "L3");

    // EG
    KnownRoom* kitchen = addKnownRoom("kitchen", "Küche");
    KnownRoom* diningRoom = addKnownRoom("diningRoom", "EZ");
    KnownRoom* toilet = addKnownRoom("toilet", "WC");
    KnownRoom* mainFloor = addKnownRoom("mainFloor", "HF");
    KnownRoom* egFloor = addKnownRoom("egFloor", "Flur");
    KnownRoom* workingRoom = addKnownRoom("workingRoom", "AZ");
    KnownRoom* supplyRoom = addKnownRoom("supplyRoom", "VZ");
    // OG
    KnownRoom* ogFloor = addKnownRoom("ogFloor", "Flur");
    KnownRoom* clothingRoom = addKnownRoom("clothingRoom", "AZ");
    KnownRoom* livingRoom = addKnownRoom("livingRoom", "WZ");
    KnownRoom* sleepingRoom = addKnownRoom("sleepingRoom", "SZ");
    KnownRoom* bathRoom = addKnownRoom("bathRoom", "Bad");
    // roof


    // RELAYS
    ValueGroup* nodeBasementRelays = addValueGroup("basementRelays0");
    heatingRoom->addActor(  addDigitalActor(nodeBasementRelays, "0", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    workshop->addActor(     addDigitalActor(nodeBasementRelays, "1", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeBasementRelays, "2", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "3", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "4", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "5", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "6", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "7", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);

    ValueGroup* nodeEGRelays = addValueGroup("egRelays0");
    kitchen->addActor(      addDigitalActor(nodeEGRelays, "0", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    diningRoom->addActor(   addDigitalActor(nodeEGRelays, "1", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    toilet->addActor(       addDigitalActor(nodeEGRelays, "2", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    mainFloor->addActor(    addDigitalActor(nodeEGRelays, "3", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    egFloor->addActor(      addDigitalActor(nodeEGRelays, "4", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    workingRoom->addActor(  addDigitalActor(nodeEGRelays, "5", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    supplyRoom->addActor(   addDigitalActor(nodeEGRelays, "6", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeEGRelays, "7", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);

    ValueGroup* nodeOGRelays = addValueGroup("ogRelays0");
    ogFloor->addActor(      addDigitalActor(nodeOGRelays, "0", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    clothingRoom->addActor( addDigitalActor(nodeOGRelays, "1", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    livingRoom->addActor(   addDigitalActor(nodeOGRelays, "2", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    sleepingRoom->addActor( addDigitalActor(nodeOGRelays, "3", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
    bathRoom->addActor(     addDigitalActor(nodeOGRelays, "4", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeOGRelays, "5", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeOGRelays, "6", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeOGRelays, "7", VALTYPE_RELAY_LIGHT, true, ValueBase::VT_MID);

                            // INPUTS
    ValueGroup* nodeBasementInputs = addValueGroup("basementInputs0");
    heatingRoom->addValue(  addBooleanValue(nodeBasementInputs, "0", VALTYPE_SWITCH, ValueBase::VT_MID));
    workshop->addValue(     addBooleanValue(nodeBasementInputs, "1", VALTYPE_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeBasementInputs, "2", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "3", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "4", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "5", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "6", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "7", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "8", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "9", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "10", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "11", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "12", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "13", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "14", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "15", VALTYPE_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeEGInputs = addValueGroup("egInputs0");
    kitchen->addValue(      addBooleanValue(nodeEGInputs, "0", VALTYPE_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeEGInputs, "1", VALTYPE_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeEGInputs, "2", VALTYPE_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeEGInputs, "3", VALTYPE_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeEGInputs, "4", VALTYPE_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeEGInputs, "5", VALTYPE_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeEGInputs, "6", VALTYPE_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeEGInputs, "7", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "8", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "9", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "10", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "11", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "12", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "13", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "14", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "15", VALTYPE_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeOGInputs = addValueGroup("ogInputs0");
    kitchen->addValue(      addBooleanValue(nodeOGInputs, "0", VALTYPE_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeOGInputs, "1", VALTYPE_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeOGInputs, "2", VALTYPE_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeOGInputs, "3", VALTYPE_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeOGInputs, "4", VALTYPE_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeOGInputs, "5", VALTYPE_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeOGInputs, "6", VALTYPE_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeOGInputs, "7", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "8", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "9", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "10", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "11", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "12", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "13", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "14", VALTYPE_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "15", VALTYPE_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeTemps = addValueGroup("temps");
    // EG
    kitchen->addValue(      addDoubleValue(nodeTemps, "20", VALTYPE_TEMP, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeTemps, "21", VALTYPE_TEMP, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeTemps, "22", VALTYPE_TEMP, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeTemps, "23", VALTYPE_TEMP, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeTemps, "24", VALTYPE_TEMP, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeTemps, "25", VALTYPE_TEMP, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeTemps, "26", VALTYPE_TEMP, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeTemps, "40", VALTYPE_TEMP, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeTemps, "41", VALTYPE_TEMP, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeTemps, "42", VALTYPE_TEMP, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeTemps, "43", VALTYPE_TEMP, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeTemps, "44", VALTYPE_TEMP, ValueBase::VT_MID));

    ValueGroup* nodeHums = addValueGroup("hums");
    // EG
    kitchen->addValue(      addDoubleValue(nodeHums, "20", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeHums, "21", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeHums, "22", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeHums, "23", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeHums, "24", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeHums, "25", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeHums, "26", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeHums, "40", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeHums, "41", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeHums, "42", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeHums, "43", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeHums, "44", VALTYPE_HUMIDITY, ValueBase::VT_MID));


    ValueGroup* nodePirs = addValueGroup("motions");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodePirs, "20", VALTYPE_MOTION, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodePirs, "21", VALTYPE_MOTION, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodePirs, "22", VALTYPE_MOTION, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodePirs, "23", VALTYPE_MOTION, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodePirs, "24", VALTYPE_MOTION, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodePirs, "25", VALTYPE_MOTION, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodePirs, "26", VALTYPE_MOTION, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodePirs, "40", VALTYPE_MOTION, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodePirs, "41", VALTYPE_MOTION, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodePirs, "42", VALTYPE_MOTION, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodePirs, "43", VALTYPE_MOTION, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodePirs, "44", VALTYPE_MOTION, ValueBase::VT_MID));

    ValueGroup* nodeBrightnesses = addValueGroup("brightnesses");
    // eg
    kitchen->addValue(      addDoubleValue(nodeBrightnesses, "20", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeBrightnesses, "21", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeBrightnesses, "22", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeBrightnesses, "23", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeBrightnesses, "24", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeBrightnesses, "25", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeBrightnesses, "26", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addDoubleValue(nodeBrightnesses, "40", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeBrightnesses, "41", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeBrightnesses, "42", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeBrightnesses, "43", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeBrightnesses, "44", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));

    ValueGroup* nodeAlarms = addValueGroup("alarms");
    // eg
    kitchen->addActor(      addDigitalActor(nodeAlarms, "20", VALTYPE_ALARM_SOUND, true, ValueBase::VT_MID));

    ValueGroup* nodeWaterFlows = addValueGroup("waterFlows");
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "toilet", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "cold", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "warm", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "garden", VALTYPE_WATER_FLOW, ValueBase::VT_MID));

    // basement
    addProcessorTask("basement.heatingRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.0', 'basementInputs0.0', 20000)");
    addProcessorTask("basement.workshop.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.1', 'basementInputs0.1', 20000)");

    // eg
    addProcessorTask("eg.kitchen.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.0', 'egInputs0.0', 'motions.20', 'brightnesses.20', 30, 20000, 5000)");
    addProcessorTask("eg.diningRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.1', 'egInputs0.1', 'motions.21', 'brightnesses.21', 30, 20000, 5000)");
    addProcessorTask("eg.toilet.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.2', 'egInputs0.2', 'motions.22', 'brightnesses.22', 30, 20000, 5000)");
    addProcessorTask("eg.mainFloor.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.3', 'egInputs0.3', 'motions.23', 'brightnesses.23', 30, 20000, 5000)");
    addProcessorTask("eg.egFloor.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.4', 'egInputs0.4', 'motions.24', 'brightnesses.24', 30, 20000, 5000)");
    addProcessorTask("eg.workingRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.5', 'egInputs0.5', 'motions.25', 'brightnesses.25', 30, 20000, 5000)");
    addProcessorTask("eg.supplyRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.6', 'egInputs0.6', 'motions.26', 'brightnesses.26', 30, 20000, 5000)");

    // og
    addProcessorTask("og.ogFloor.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.0', 'ogInputs0.0', 'motions.40', 'brightnesses.40', 30, 20000, 5000)");
    addProcessorTask("og.clothingRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.1', 'ogInputs0.1', 'motions.41', 'brightnesses.41', 30, 20000, 5000)");
    addProcessorTask("og.livingRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.2', 'ogInputs0.2', 'motions.42', 'brightnesses.42', 30, 20000, 5000)");
    addProcessorTask("og.sleepingRoom.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.3', 'ogInputs0.4', 'motions.43', 'brightnesses.43', 30, 20000, 5000)");
    addProcessorTask("og.bathFloor.light", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.4', 'ogInputs0.4', 'motions.44', 'brightnesses.44', 30, 20000, 5000)");

    //addProcessorTask("egRelays0", "values_egRelays0_0.rawValue()");
    //addProcessorTask("egInputs0", "values_egInputs0_0.rawValue()");
    //addProcessorTask("logicproc1", "CommonScripts.ensureState(values_egRelays0_0, values_egInputs0_0, false, function(expected) {values_egRelays0_0.triggerCmd(expected ? C.ACTOR_CMD_ON : C.ACTOR_CMD_OFF )} );");

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
        QString valueGroupId = obj.value("valueGroup").toString();

        if (m_valueGroups.contains(valueGroupId)) {
            newInstance->setValueGroup(m_valueGroups.value(valueGroupId));
        } else {
            iWarning() << "Unable to resolve value group id" << valueGroupId;
        }
        return newInstance->fullId();
    });

    deserializeMap(doc.object(), "actors", m_actors, [this](ActorBase* newInstance, QJsonObject obj) {
        QString valueGroupId = obj.value("valueGroup").toString();

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
    deserializeMap(doc.object(), "processorTasks", m_processorTasks, [](NativeProcessorTask* newInstance, QJsonObject) { return newInstance->id(); });
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
        } else if (classType == NativeProcessorTask::staticMetaObject.className()) {
            newInstance = new NativeProcessorTask();
        } else {
            qFatal("Unsupported class type");
        }

        newInstance->deserialize(arr.at(i).toObject());
        //QString id = setupFunc((T)newInstance, dataObj);
        QString id = "TBD";
        map.insert(id, (T)newInstance);
    }
}
