#include "testdatamodel.h"

#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "value/doublevalue.h"
#include "processor/server/processortask.h"
#include <QDebug>

TestDatamodel::TestDatamodel(QObject *parent) : DatamodelBase("testdatamodel", parent) {
    iDebug() << Q_FUNC_INFO;

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
    heatingRoom->addActor(  addDigitalActor(nodeBasementRelays, "0", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    workshop->addActor(     addDigitalActor(nodeBasementRelays, "1", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeBasementRelays, "2", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "3", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "4", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "5", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "6", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeBasementRelays, "7", VT_RELAY_LIGHT, true, ValueBase::VT_MID);

    ValueGroup* nodeEGRelays = addValueGroup("egRelays0");
    kitchen->addActor(      addDigitalActor(nodeEGRelays, "0", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    diningRoom->addActor(   addDigitalActor(nodeEGRelays, "1", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    toilet->addActor(       addDigitalActor(nodeEGRelays, "2", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    mainFloor->addActor(    addDigitalActor(nodeEGRelays, "3", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    egFloor->addActor(      addDigitalActor(nodeEGRelays, "4", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    workingRoom->addActor(  addDigitalActor(nodeEGRelays, "5", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    supplyRoom->addActor(   addDigitalActor(nodeEGRelays, "6", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeEGRelays, "7", VT_RELAY_LIGHT, true, ValueBase::VT_MID);

    ValueGroup* nodeOGRelays = addValueGroup("ogRelays0");
    ogFloor->addActor(      addDigitalActor(nodeOGRelays, "0", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    clothingRoom->addActor( addDigitalActor(nodeOGRelays, "1", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    livingRoom->addActor(   addDigitalActor(nodeOGRelays, "2", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    sleepingRoom->addActor( addDigitalActor(nodeOGRelays, "3", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    bathRoom->addActor(     addDigitalActor(nodeOGRelays, "4", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeOGRelays, "5", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeOGRelays, "6", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeOGRelays, "7", VT_RELAY_LIGHT, true, ValueBase::VT_MID);

                            // INPUTS
    ValueGroup* nodeBasementInputs = addValueGroup("basementInputs0");
    heatingRoom->addValue(  addBooleanValue(nodeBasementInputs, "0", VT_SWITCH, ValueBase::VT_MID));
    workshop->addValue(     addBooleanValue(nodeBasementInputs, "1", VT_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeBasementInputs, "2", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "3", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "4", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "5", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "6", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "7", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "8", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "9", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "10", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "11", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "12", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "13", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "14", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeBasementInputs, "15", VT_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeEGInputs = addValueGroup("egInputs0");
    kitchen->addValue(      addBooleanValue(nodeEGInputs, "0", VT_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeEGInputs, "1", VT_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeEGInputs, "2", VT_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeEGInputs, "3", VT_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeEGInputs, "4", VT_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeEGInputs, "5", VT_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeEGInputs, "6", VT_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeEGInputs, "7", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "8", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "9", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "10", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "11", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "12", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "13", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "14", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "15", VT_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeOGInputs = addValueGroup("ogInputs0");
    kitchen->addValue(      addBooleanValue(nodeOGInputs, "0", VT_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeOGInputs, "1", VT_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeOGInputs, "2", VT_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeOGInputs, "3", VT_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeOGInputs, "4", VT_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeOGInputs, "5", VT_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeOGInputs, "6", VT_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeOGInputs, "7", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "8", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "9", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "10", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "11", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "12", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "13", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "14", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "15", VT_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeTemps = addValueGroup("temps");
    // EG
    kitchen->addValue(      addDoubleValue(nodeTemps, "20", VT_TEMP, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeTemps, "21", VT_TEMP, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeTemps, "22", VT_TEMP, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeTemps, "23", VT_TEMP, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeTemps, "24", VT_TEMP, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeTemps, "25", VT_TEMP, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeTemps, "26", VT_TEMP, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeTemps, "40", VT_TEMP, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeTemps, "41", VT_TEMP, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeTemps, "42", VT_TEMP, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeTemps, "43", VT_TEMP, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeTemps, "44", VT_TEMP, ValueBase::VT_MID));

    ValueGroup* nodeHums = addValueGroup("hums");
    // EG
    kitchen->addValue(      addDoubleValue(nodeHums, "20", VT_HUMIDITY, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeHums, "21", VT_HUMIDITY, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeHums, "22", VT_HUMIDITY, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeHums, "23", VT_HUMIDITY, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeHums, "24", VT_HUMIDITY, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeHums, "25", VT_HUMIDITY, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeHums, "26", VT_HUMIDITY, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeHums, "40", VT_HUMIDITY, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeHums, "41", VT_HUMIDITY, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeHums, "42", VT_HUMIDITY, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeHums, "43", VT_HUMIDITY, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeHums, "44", VT_HUMIDITY, ValueBase::VT_MID));


    ValueGroup* nodePirs = addValueGroup("motions");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodePirs, "20", VT_MOTION, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodePirs, "21", VT_MOTION, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodePirs, "22", VT_MOTION, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodePirs, "23", VT_MOTION, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodePirs, "24", VT_MOTION, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodePirs, "25", VT_MOTION, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodePirs, "26", VT_MOTION, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodePirs, "40", VT_MOTION, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodePirs, "41", VT_MOTION, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodePirs, "42", VT_MOTION, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodePirs, "43", VT_MOTION, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodePirs, "44", VT_MOTION, ValueBase::VT_MID));

    ValueGroup* nodeBrightnesses = addValueGroup("brightnesses");
    // eg
    kitchen->addValue(      addDoubleValue(nodeBrightnesses, "20", VT_BRIGHTNESS, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeBrightnesses, "21", VT_BRIGHTNESS, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeBrightnesses, "22", VT_BRIGHTNESS, ValueBase::VT_MID));
    mainFloor->addValue(    addDoubleValue(nodeBrightnesses, "23", VT_BRIGHTNESS, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeBrightnesses, "24", VT_BRIGHTNESS, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeBrightnesses, "25", VT_BRIGHTNESS, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeBrightnesses, "26", VT_BRIGHTNESS, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addDoubleValue(nodeBrightnesses, "40", VT_BRIGHTNESS, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeBrightnesses, "41", VT_BRIGHTNESS, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeBrightnesses, "42", VT_BRIGHTNESS, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeBrightnesses, "43", VT_BRIGHTNESS, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeBrightnesses, "44", VT_BRIGHTNESS, ValueBase::VT_MID));

    ValueGroup* nodeAlarms = addValueGroup("alarms");
    // eg
    kitchen->addActor(      addDigitalActor(nodeAlarms, "20", VT_ALARM_SOUND, true, ValueBase::VT_MID));

    ValueGroup* nodeWaterFlows = addValueGroup("waterFlows");
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "toilet", VT_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "cold", VT_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "warm", VT_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "garden", VT_WATER_FLOW, ValueBase::VT_MID));

    ValueGroup* nodeWaterLevels = addValueGroup("waterLevels");
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "toilet", VT_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "cold", VT_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "warm", VT_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "garden", VT_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));

    // basement
    addProcessorTask("basement.heatingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.0', 'basementInputs0.0', 20000)");
    addProcessorTask("basement.workshop.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.1', 'basementInputs0.1', 20000)");

    /*
    // eg
    addProcessorTask("eg.kitchen.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.0', 'egInputs0.0', 'motions.20', 'brightnesses.20', 30, 20000, 5000)");
    addProcessorTask("eg.diningRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.1', 'egInputs0.1', 'motions.21', 'brightnesses.21', 30, 20000, 5000)");
    addProcessorTask("eg.toilet.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.2', 'egInputs0.2', 'motions.22', 'brightnesses.22', 30, 20000, 5000)");
    addProcessorTask("eg.mainFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.3', 'egInputs0.3', 'motions.23', 'brightnesses.23', 30, 20000, 5000)");
    addProcessorTask("eg.egFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.4', 'egInputs0.4', 'motions.24', 'brightnesses.24', 30, 20000, 5000)");
    addProcessorTask("eg.workingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.5', 'egInputs0.5', 'motions.25', 'brightnesses.25', 30, 20000, 5000)");
    addProcessorTask("eg.supplyRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('egRelays0.6', 'egInputs0.6', 'motions.26', 'brightnesses.26', 30, 20000, 5000)");

    // og
    addProcessorTask("og.ogFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.0', 'ogInputs0.0', 'motions.40', 'brightnesses.40', 30, 20000, 5000)");
    addProcessorTask("og.clothingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.1', 'ogInputs0.1', 'motions.41', 'brightnesses.41', 30, 20000, 5000)");
    addProcessorTask("og.livingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.2', 'ogInputs0.2', 'motions.42', 'brightnesses.42', 30, 20000, 5000)");
    addProcessorTask("og.sleepingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.3', 'ogInputs0.4', 'motions.43', 'brightnesses.43', 30, 20000, 5000)");
    addProcessorTask("og.bathFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('ogRelays0.4', 'ogInputs0.4', 'motions.44', 'brightnesses.44', 30, 20000, 5000)");
    */

    //addProcessorTask("egRelays0", "values_egRelays0_0.rawValue()");
    //addProcessorTask("egInputs0", "values_egInputs0_0.rawValue()");
    //addProcessorTask("logicproc1", "CommonScripts.ensureState(values_egRelays0_0, values_egInputs0_0, false, function(expected) {values_egRelays0_0.triggerCmd(expected ? C.ACTOR_CMD_ON : C.ACTOR_CMD_OFF )} );");
}
