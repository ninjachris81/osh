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


    // TEMP VALVES
    ValueGroup* nodeTempValves = addValueGroup("tempValves");
    heatingRoom->addActor(  addDigitalActor(nodeTempValves, "0", VT_RELAY_TEMP_VALVE, true, ValueBase::VT_MID));

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

    ValueGroup* nodeEGOGRelays = addValueGroup("lightRelays");
    kitchen->addActor(      addDigitalActor(nodeEGOGRelays, "0", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    diningRoom->addActor(   addDigitalActor(nodeEGOGRelays, "1", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    toilet->addActor(       addDigitalActor(nodeEGOGRelays, "2", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    mainFloor->addActor(    addDigitalActor(nodeEGOGRelays, "3", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    egFloor->addActor(      addDigitalActor(nodeEGOGRelays, "4", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    workingRoom->addActor(  addDigitalActor(nodeEGOGRelays, "5", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    supplyRoom->addActor(   addDigitalActor(nodeEGOGRelays, "6", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeEGOGRelays, "7", VT_RELAY_LIGHT, true, ValueBase::VT_MID);

    ogFloor->addActor(      addDigitalActor(nodeEGOGRelays, "15", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    clothingRoom->addActor( addDigitalActor(nodeEGOGRelays, "16", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    livingRoom->addActor(   addDigitalActor(nodeEGOGRelays, "17", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    sleepingRoom->addActor( addDigitalActor(nodeEGOGRelays, "18", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
    bathRoom->addActor(     addDigitalActor(nodeEGOGRelays, "19", VT_RELAY_LIGHT, true, ValueBase::VT_MID));
                            addDigitalActor(nodeEGOGRelays, "20", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeEGOGRelays, "21", VT_RELAY_LIGHT, true, ValueBase::VT_MID);
                            addDigitalActor(nodeEGOGRelays, "22", VT_RELAY_LIGHT, true, ValueBase::VT_MID);

    // SHUTTERS
    ValueGroup* nodeShutterStates = addValueGroup("shutterStates");
    ValueGroup* nodeShutterCloseStates = addValueGroup("shutterCloseStates");
    ValueGroup* nodeShutterTiltStates = addValueGroup("shutterTiltStates");

    kitchen->addActor(      addShutterActor(nodeShutterStates, nodeShutterCloseStates, "20", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    diningRoom->addActor(   addShutterActor(nodeShutterStates, nodeShutterCloseStates, nodeShutterTiltStates, "21", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    toilet->addActor(       addShutterActor(nodeShutterStates, nodeShutterCloseStates, "22", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    mainFloor->addActor(    addShutterActor(nodeShutterStates, nodeShutterCloseStates, "23", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    egFloor->addActor(      addShutterActor(nodeShutterStates, nodeShutterCloseStates, "24", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    workingRoom->addActor(  addShutterActor(nodeShutterStates, nodeShutterCloseStates, nodeShutterTiltStates, "25", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    supplyRoom->addActor(   addShutterActor(nodeShutterStates, nodeShutterCloseStates, "26", VT_RELAY_SHUTTER, ValueBase::VT_MID));

    ogFloor->addActor(      addShutterActor(nodeShutterStates, nodeShutterCloseStates, "40", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    clothingRoom->addActor( addShutterActor(nodeShutterStates, nodeShutterCloseStates, "41", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    livingRoom->addActor(   addShutterActor(nodeShutterStates, nodeShutterCloseStates, nodeShutterTiltStates, "42", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    sleepingRoom->addActor( addShutterActor(nodeShutterStates, nodeShutterCloseStates, nodeShutterTiltStates, "43", VT_RELAY_SHUTTER, ValueBase::VT_MID));
    bathRoom->addActor(     addShutterActor(nodeShutterStates, nodeShutterCloseStates, "44", VT_RELAY_SHUTTER, ValueBase::VT_MID));

    // REED CONTACTS
    ValueGroup* nodeReedContacts = addValueGroup("reedContacts");
    kitchen->addValue(      addBooleanValue(nodeReedContacts, "20", VT_REED_CONTACT, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeReedContacts, "21", VT_REED_CONTACT, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeReedContacts, "22", VT_REED_CONTACT, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeReedContacts, "23", VT_REED_CONTACT, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeReedContacts, "24", VT_REED_CONTACT, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeReedContacts, "25", VT_REED_CONTACT, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeReedContacts, "26", VT_REED_CONTACT, ValueBase::VT_MID));

    ogFloor->addValue(      addBooleanValue(nodeReedContacts, "40", VT_REED_CONTACT, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeReedContacts, "41", VT_REED_CONTACT, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeReedContacts, "42", VT_REED_CONTACT, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodeReedContacts, "43", VT_REED_CONTACT, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeReedContacts, "44", VT_REED_CONTACT, ValueBase::VT_MID));

    // SWITCHES
    ValueGroup* nodeSwitches = addValueGroup("switches");
    heatingRoom->addValue(  addBooleanValue(nodeSwitches, "0", VT_SWITCH, ValueBase::VT_MID));
    workshop->addValue(     addBooleanValue(nodeSwitches, "1", VT_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeSwitches, "2", VT_SWITCH, ValueBase::VT_MID);
                            /*
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
                            */

    kitchen->addValue(      addBooleanValue(nodeSwitches, "20", VT_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeSwitches, "21", VT_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeSwitches, "22", VT_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeSwitches, "23", VT_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeSwitches, "24", VT_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeSwitches, "25", VT_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeSwitches, "26", VT_SWITCH, ValueBase::VT_MID));
    /*
                            addBooleanValue(nodeEGInputs, "7", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "8", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "9", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "10", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "11", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "12", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "13", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "14", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeEGInputs, "15", VT_SWITCH, ValueBase::VT_MID);
                            */

    kitchen->addValue(      addBooleanValue(nodeSwitches, "40", VT_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeSwitches, "41", VT_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeSwitches, "42", VT_SWITCH, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeSwitches, "43", VT_SWITCH, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeSwitches, "44", VT_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeSwitches, "45", VT_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeSwitches, "46", VT_SWITCH, ValueBase::VT_MID));
    /*
                            addBooleanValue(nodeOGInputs, "7", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "8", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "9", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "10", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "11", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "12", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "13", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "14", VT_SWITCH, ValueBase::VT_MID);
                            addBooleanValue(nodeOGInputs, "15", VT_SWITCH, ValueBase::VT_MID);
                            */

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

    ValueGroup* nodeTargetTemps = addValueGroup("targetTemps");
    // EG
    kitchen->addValue(      addDoubleValue(nodeTargetTemps, "20", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    diningRoom->addValue(   addDoubleValue(nodeTargetTemps, "21", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    toilet->addValue(       addDoubleValue(nodeTargetTemps, "22", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    mainFloor->addValue(    addDoubleValue(nodeTargetTemps, "23", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    egFloor->addValue(      addDoubleValue(nodeTargetTemps, "24", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    workingRoom->addValue(  addDoubleValue(nodeTargetTemps, "25", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    supplyRoom->addValue(   addDoubleValue(nodeTargetTemps, "26", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeTargetTemps, "40", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    clothingRoom->addValue( addDoubleValue(nodeTargetTemps, "41", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    livingRoom->addValue(   addDoubleValue(nodeTargetTemps, "42", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    sleepingRoom->addValue( addDoubleValue(nodeTargetTemps, "43", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    bathRoom->addValue(     addDoubleValue(nodeTargetTemps, "44", VT_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));

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


    ValueGroup* nodeMotions = addValueGroup("motions");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodeMotions, "20", VT_MOTION, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeMotions, "21", VT_MOTION, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeMotions, "22", VT_MOTION, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeMotions, "23", VT_MOTION, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeMotions, "24", VT_MOTION, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeMotions, "25", VT_MOTION, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeMotions, "26", VT_MOTION, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodeMotions, "40", VT_MOTION, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeMotions, "41", VT_MOTION, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeMotions, "42", VT_MOTION, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodeMotions, "43", VT_MOTION, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeMotions, "44", VT_MOTION, ValueBase::VT_MID));

    ValueGroup* nodePirs = addValueGroup("motions_pirs");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodePirs, "20", VT_MOTION_PIR, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodePirs, "21", VT_MOTION_PIR, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodePirs, "22", VT_MOTION_PIR, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodePirs, "23", VT_MOTION_PIR, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodePirs, "24", VT_MOTION_PIR, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodePirs, "25", VT_MOTION_PIR, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodePirs, "26", VT_MOTION_PIR, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodePirs, "40", VT_MOTION_PIR, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodePirs, "41", VT_MOTION_PIR, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodePirs, "42", VT_MOTION_PIR, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodePirs, "43", VT_MOTION_PIR, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodePirs, "44", VT_MOTION_PIR, ValueBase::VT_MID));

    ValueGroup* nodeRadars = addValueGroup("motions_radars");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodeRadars, "20", VT_MOTION_RADAR, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeRadars, "21", VT_MOTION_RADAR, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeRadars, "22", VT_MOTION_RADAR, ValueBase::VT_MID));
    mainFloor->addValue(    addBooleanValue(nodeRadars, "23", VT_MOTION_RADAR, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeRadars, "24", VT_MOTION_RADAR, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeRadars, "25", VT_MOTION_RADAR, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeRadars, "26", VT_MOTION_RADAR, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodeRadars, "40", VT_MOTION_RADAR, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeRadars, "41", VT_MOTION_RADAR, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeRadars, "42", VT_MOTION_RADAR, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodeRadars, "43", VT_MOTION_RADAR, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeRadars, "44", VT_MOTION_RADAR, ValueBase::VT_MID));

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
    diningRoom->addActor(   addDigitalActor(nodeAlarms, "21", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    toilet->addActor(       addDigitalActor(nodeAlarms, "22", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    mainFloor->addActor(    addDigitalActor(nodeAlarms, "23", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    egFloor->addActor(      addDigitalActor(nodeAlarms, "24", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    workingRoom->addActor(  addDigitalActor(nodeAlarms, "25", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    supplyRoom->addActor(   addDigitalActor(nodeAlarms, "26", VT_ALARM_SOUND, true, ValueBase::VT_MID));

    ogFloor->addValue(      addDigitalActor(nodeBrightnesses, "40", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    clothingRoom->addValue( addDigitalActor(nodeBrightnesses, "41", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    livingRoom->addValue(   addDigitalActor(nodeBrightnesses, "42", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    sleepingRoom->addValue( addDigitalActor(nodeBrightnesses, "43", VT_ALARM_SOUND, true, ValueBase::VT_MID));
    bathRoom->addValue(     addDigitalActor(nodeBrightnesses, "44", VT_ALARM_SOUND, true, ValueBase::VT_MID));

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

    /*
    // test interval
    addProcessorTask("test", ProcessorTask::PTT_ONLY_ONCE, "CommonScripts.setupInterval('test', 1000, 5000, false)");
    addProcessorTask("test2", ProcessorTask::PTT_INTERVAL, "CommonScripts.getIntervalState('test')");
    */

    //addProcessorTask("eg.tempValve.kitchen", ProcessorTask::PTT_INTERVAL, "CommonScripts.applyTempValveLogic('temps.20', 'targetTemps.20', 'tempValves.20', 30000)", "", 1000);


    addProcessorTask("eg.motion.feg", ProcessorTask::PTT_INTERVAL, "CommonScripts.applyMotionLogic('motions_radars.24', 'motions_pirs.24', 'motions.24')", "", 500);
    addProcessorTask("eg.egFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('lightRelays.4', 'switches.24', 'motions.24', 'brightnesses.24', 20, 20000, 5000)");

    /*
    // basement
    addProcessorTask("basement.heatingRoom.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.0', 'basementInputs0.0', 20000)");
    addProcessorTask("basement.workshop.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchLogic('basementRelays0.1', 'basementInputs0.1', 20000)");

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
