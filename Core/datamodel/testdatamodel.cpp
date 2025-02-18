#include "testdatamodel.h"

#include "actor/digitalactor.h"
#include "value/booleanvalue.h"
#include "value/doublevalue.h"
#include "processor/processortaskbase.h"
#include <QDebug>

TestDatamodel::TestDatamodel(ProcessorTaskFactory *processorTaskFactory, QObject *parent) : DatamodelBase("testdatamodel", parent) {
    iDebug() << Q_FUNC_INFO;

    setProcessorTaskFactory(processorTaskFactory);

    // DEVICES
    addKnownDevice("349785676", "CoreServer", "Server");
    addKnownDevice("582645258", "CoreUI", "GUI");
    addKnownDevice("1306476338", "InputService", "EG-OG Input");
    addKnownDevice("1718100386", "RelayService", "EG-OG Relay");
    addKnownDevice("1718100387", "RelayShutterService", "EG-OG Shutter");
    addKnownDevice("0020", "SensorService_20", "Sensor EG Küche");

    // AREAS
    KnownArea* basement = addKnownArea("basement", "Keller");
    KnownArea* eg = addKnownArea("eg", "EG");
    KnownArea* og = addKnownArea("og", "OG");
    KnownArea* dg = addKnownArea("dg", "DG");
    KnownArea* garden = addKnownArea("garden", "Garten");

    // ROOMS
    // BASEMENT
    KnownRoom* heatingRoom = addKnownRoom(basement, "heatingRoom", "Heizraum");
    KnownRoom* workshop = addKnownRoom(basement, "workshop", "Werkstatt");
    KnownRoom* basementFloor0 = addKnownRoom(basement, "basementFloor0", "HF");
    KnownRoom* basementFloor1 = addKnownRoom(basement, "basementFloor1", "Flur");
    KnownRoom* storage1 = addKnownRoom(basement, "storage1", "L1");
    KnownRoom* storage2 = addKnownRoom(basement, "storage2", "L2");
    KnownRoom* storage3 = addKnownRoom(basement, "storage3", "L3");

    // EG
    KnownRoom* egFloor = addKnownRoom(eg, "feg", "Flur");
    KnownRoom* workingRoom = addKnownRoom(eg, "az", "AZ");
    KnownRoom* kitchen = addKnownRoom(eg, "k", "Küche");
    KnownRoom* diningRoom = addKnownRoom(eg, "ez", "EZ");
    KnownRoom* toilet = addKnownRoom(eg, "wc", "WC");
    KnownRoom* supplyRoom = addKnownRoom(eg, "vz", "VZ");
    KnownRoom* egMainFloor = addKnownRoom(eg, "hfe", "HFE");
    KnownRoom* egSideFloor = addKnownRoom(eg, "nfe", "NFE");

    // OG
    KnownRoom* sleepingRoom = addKnownRoom(og, "sz", "SZ");
    KnownRoom* clothingRoom = addKnownRoom(og, "uz", "UZ");
    KnownRoom* bathRoom = addKnownRoom(og, "b", "Bad");
    KnownRoom* livingRoom = addKnownRoom(og, "wz", "WZ");
    KnownRoom* ogFloor = addKnownRoom(og, "fog", "Flur");
    KnownRoom* ogMainFloor = addKnownRoom(og, "hfo", "HFO");

    // roof
    ValueGroup* lightToggles = addValueGroup("lightToggles0");
    egFloor->addActor(      addToggleActor(lightToggles, "0"));
    workingRoom->addActor(  addToggleActor(lightToggles, "1"));
    kitchen->addActor(      addToggleActor(lightToggles, "2"));
    diningRoom->addActor(   addToggleActor(lightToggles, "3"));
    toilet->addActor(       addToggleActor(lightToggles, "4"));
    supplyRoom->addActor(   addToggleActor(lightToggles, "5"));
    egMainFloor->addActor(  addToggleActor(lightToggles, "6"));
    egSideFloor->addActor(  addToggleActor(lightToggles, "7"));

    sleepingRoom->addActor( addToggleActor(lightToggles, "8"));
    clothingRoom->addActor( addToggleActor(lightToggles, "9"));
    bathRoom->addActor(     addToggleActor(lightToggles, "10"));
    livingRoom->addActor(   addToggleActor(lightToggles, "11"));
    ogFloor->addActor(      addToggleActor(lightToggles, "12"));
    ogMainFloor->addActor(  addToggleActor(lightToggles, "13"));

    // TEMP VALVES
    ValueGroup* nodeTempValves = addValueGroup("tempValves");
    heatingRoom->addActor(  addDigitalActor(nodeTempValves, "0", VALTYPE_RELAY_TEMP_VALVE, ValueBase::VT_MID, true));

    // RELAYS
    ValueGroup* nodeBasementRelays = addValueGroup("basementRelays0");
    heatingRoom->addActor(  addDigitalActor(nodeBasementRelays, "0", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    workshop->addActor(     addDigitalActor(nodeBasementRelays, "1", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
                            addDigitalActor(nodeBasementRelays, "2", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeBasementRelays, "3", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeBasementRelays, "4", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeBasementRelays, "5", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeBasementRelays, "6", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeBasementRelays, "7", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);

    ValueGroup* nodeAllRelays0 = addValueGroup("allRelays0");

    // EG
    egFloor->addActor(      addDigitalActor(nodeAllRelays0, "0", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    workingRoom->addActor(  addDigitalActor(nodeAllRelays0, "1", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    kitchen->addActor(      addDigitalActor(nodeAllRelays0, "2", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    diningRoom->addActor(   addDigitalActor(nodeAllRelays0, "3", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    toilet->addActor(       addDigitalActor(nodeAllRelays0, "4", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    supplyRoom->addActor(   addDigitalActor(nodeAllRelays0, "5", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    egMainFloor->addActor(  addDigitalActor(nodeAllRelays0, "6", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    egSideFloor->addActor(  addDigitalActor(nodeAllRelays0, "7", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));

    // OG
    sleepingRoom->addActor( addDigitalActor(nodeAllRelays0, "16", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    clothingRoom->addActor( addDigitalActor(nodeAllRelays0, "17", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    bathRoom->addActor(     addDigitalActor(nodeAllRelays0, "18", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    livingRoom->addActor(   addDigitalActor(nodeAllRelays0, "19", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    ogFloor->addActor(      addDigitalActor(nodeAllRelays0, "20", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
    ogMainFloor->addActor(  addDigitalActor(nodeAllRelays0, "21", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true));
                            addDigitalActor(nodeAllRelays0, "22", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);
                            addDigitalActor(nodeAllRelays0, "23", VALTYPE_RELAY_LIGHT, ValueBase::VT_MID, true);

    // SHUTTERS
    ValueGroup* nodeAllShutters = addValueGroup("allShutters0");

    workingRoom->addActor(  addShutterActor(nodeAllShutters, "0", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    kitchen->addActor(      addShutterActor(nodeAllShutters, "1", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    diningRoom->addActor(   addShutterActor(nodeAllShutters, "2", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 30000, 0));
    toilet->addActor(       addShutterActor(nodeAllShutters, "3", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    supplyRoom->addActor(   addShutterActor(nodeAllShutters, "4", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    egSideFloor->addActor(  addShutterActor(nodeAllShutters, "5", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));

    sleepingRoom->addActor( addShutterActor(nodeAllShutters, "6", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, true, 50000, 2000));
    clothingRoom->addActor( addShutterActor(nodeAllShutters, "7", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    bathRoom->addActor(     addShutterActor(nodeAllShutters, "8", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, false, 20000, 0));
    livingRoom->addActor(   addShutterActor(nodeAllShutters, "9", VALTYPE_RELAY_SHUTTER, ValueBase::VT_NONE, true, 50000, 2000));

    ValueGroup* nodeShutterRelays0 = addValueGroup("shutterRelays0");

    // shutter relays
    workingRoom->addActor(  addDigitalActor(nodeShutterRelays0, "0", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    workingRoom->addActor(  addDigitalActor(nodeShutterRelays0, "1", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    kitchen->addActor(      addDigitalActor(nodeShutterRelays0, "2", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    kitchen->addActor(      addDigitalActor(nodeShutterRelays0, "3", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    diningRoom->addActor(   addDigitalActor(nodeShutterRelays0, "4", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    diningRoom->addActor(   addDigitalActor(nodeShutterRelays0, "5", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    toilet->addActor(       addDigitalActor(nodeShutterRelays0, "6", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    toilet->addActor(       addDigitalActor(nodeShutterRelays0, "7", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    supplyRoom->addActor(   addDigitalActor(nodeShutterRelays0, "8", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    supplyRoom->addActor(   addDigitalActor(nodeShutterRelays0, "9", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    egSideFloor->addActor(  addDigitalActor(nodeShutterRelays0, "10", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    egSideFloor->addActor(  addDigitalActor(nodeShutterRelays0, "11", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));

    // shutter replays
    sleepingRoom->addActor( addDigitalActor(nodeShutterRelays0, "12", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    sleepingRoom->addActor( addDigitalActor(nodeShutterRelays0, "13", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    clothingRoom->addActor( addDigitalActor(nodeShutterRelays0, "14", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    clothingRoom->addActor( addDigitalActor(nodeShutterRelays0, "15", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    bathRoom->addActor(     addDigitalActor(nodeShutterRelays0, "16", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    bathRoom->addActor(     addDigitalActor(nodeShutterRelays0, "17", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    livingRoom->addActor(   addDigitalActor(nodeShutterRelays0, "18", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));
    livingRoom->addActor(   addDigitalActor(nodeShutterRelays0, "19", value::VALTYPE_RELAY_SHUTTER, ValueBase::VT_MID, true));

    // REED CONTACTS
    ValueGroup* nodeReedContacts = addValueGroup("reedContacts");
    kitchen->addValue(      addBooleanValue(nodeReedContacts, "20", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeReedContacts, "21", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeReedContacts, "22", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    egMainFloor->addValue(    addBooleanValue(nodeReedContacts, "23", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeReedContacts, "24", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeReedContacts, "25", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeReedContacts, "26", VALTYPE_REED_CONTACT, ValueBase::VT_MID));

    ogFloor->addValue(      addBooleanValue(nodeReedContacts, "40", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeReedContacts, "41", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeReedContacts, "42", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodeReedContacts, "43", VALTYPE_REED_CONTACT, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeReedContacts, "44", VALTYPE_REED_CONTACT, ValueBase::VT_MID));

    // SWITCHES
    ValueGroup* nodeBasementSwitches = addValueGroup("basementSwitches");
    // Basement
    heatingRoom->addValue(  addBooleanValue(nodeBasementSwitches, "0", VALTYPE_SWITCH, ValueBase::VT_MID));
    workshop->addValue(     addBooleanValue(nodeBasementSwitches, "1", VALTYPE_SWITCH, ValueBase::VT_MID));
                            addBooleanValue(nodeBasementSwitches, "2", VALTYPE_SWITCH, ValueBase::VT_MID);

    ValueGroup* nodeAllSwitches0 = addValueGroup("allSwitches0");
    // EG
    egFloor->addValue(      addBooleanValue(nodeAllSwitches0, "0", VALTYPE_SWITCH, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeAllSwitches0, "1", VALTYPE_SWITCH, ValueBase::VT_MID));
    kitchen->addValue(      addBooleanValue(nodeAllSwitches0, "2", VALTYPE_SWITCH, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeAllSwitches0, "3", VALTYPE_SWITCH, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeAllSwitches0, "4", VALTYPE_SWITCH, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeAllSwitches0, "5", VALTYPE_SWITCH, ValueBase::VT_MID));
    egMainFloor->addValue(  addBooleanValue(nodeAllSwitches0, "6", VALTYPE_SWITCH, ValueBase::VT_MID));
    egSideFloor->addValue(  addBooleanValue(nodeAllSwitches0, "7", VALTYPE_SWITCH, ValueBase::VT_MID));

    // OG
    sleepingRoom->addValue( addBooleanValue(nodeAllSwitches0, "8", VALTYPE_SWITCH, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeAllSwitches0, "9", VALTYPE_SWITCH, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeAllSwitches0, "10", VALTYPE_SWITCH, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeAllSwitches0, "11", VALTYPE_SWITCH, ValueBase::VT_MID));
    ogFloor->addValue(      addBooleanValue(nodeAllSwitches0, "12", VALTYPE_SWITCH, ValueBase::VT_MID));
    ogMainFloor->addValue(  addBooleanValue(nodeAllSwitches0, "13", VALTYPE_SWITCH, ValueBase::VT_MID));

    ValueGroup* nodeTemps = addValueGroup("temps");
    // EG
    kitchen->addValue(      addDoubleValue(nodeTemps, "20", VALTYPE_TEMP, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeTemps, "21", VALTYPE_TEMP, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeTemps, "22", VALTYPE_TEMP, ValueBase::VT_MID));
    egMainFloor->addValue(    addDoubleValue(nodeTemps, "23", VALTYPE_TEMP, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeTemps, "24", VALTYPE_TEMP, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeTemps, "25", VALTYPE_TEMP, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeTemps, "26", VALTYPE_TEMP, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeTemps, "40", VALTYPE_TEMP, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeTemps, "41", VALTYPE_TEMP, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeTemps, "42", VALTYPE_TEMP, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeTemps, "43", VALTYPE_TEMP, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeTemps, "44", VALTYPE_TEMP, ValueBase::VT_MID));

    ValueGroup* nodeTargetTemps = addValueGroup("targetTemps");
    // EG
    kitchen->addValue(      addDoubleValue(nodeTargetTemps, "20", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    diningRoom->addValue(   addDoubleValue(nodeTargetTemps, "21", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    toilet->addValue(       addDoubleValue(nodeTargetTemps, "22", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    egMainFloor->addValue(    addDoubleValue(nodeTargetTemps, "23", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    egFloor->addValue(      addDoubleValue(nodeTargetTemps, "24", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    workingRoom->addValue(  addDoubleValue(nodeTargetTemps, "25", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    supplyRoom->addValue(   addDoubleValue(nodeTargetTemps, "26", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeTargetTemps, "40", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    clothingRoom->addValue( addDoubleValue(nodeTargetTemps, "41", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    livingRoom->addValue(   addDoubleValue(nodeTargetTemps, "42", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    sleepingRoom->addValue( addDoubleValue(nodeTargetTemps, "43", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));
    bathRoom->addValue(     addDoubleValue(nodeTargetTemps, "44", VALTYPE_STATIC_TEMP, ValueBase::VT_NONE)->withPersist(true));

    ValueGroup* nodeHums = addValueGroup("hums");
    // EG
    kitchen->addValue(      addDoubleValue(nodeHums, "20", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeHums, "21", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeHums, "22", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    egMainFloor->addValue(  addDoubleValue(nodeHums, "23", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    egFloor->addValue(      addDoubleValue(nodeHums, "24", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    workingRoom->addValue(  addDoubleValue(nodeHums, "25", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    supplyRoom->addValue(   addDoubleValue(nodeHums, "26", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    // OG
    ogFloor->addValue(      addDoubleValue(nodeHums, "40", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    clothingRoom->addValue( addDoubleValue(nodeHums, "41", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    livingRoom->addValue(   addDoubleValue(nodeHums, "42", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    sleepingRoom->addValue( addDoubleValue(nodeHums, "43", VALTYPE_HUMIDITY, ValueBase::VT_MID));
    bathRoom->addValue(     addDoubleValue(nodeHums, "44", VALTYPE_HUMIDITY, ValueBase::VT_MID));


    ValueGroup* nodeMotions = addValueGroup("motions");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    egFloor->addValue(      addBooleanValue(nodeMotions, "20", VALTYPE_MOTION, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeMotions, "21", VALTYPE_MOTION, ValueBase::VT_MID));
    kitchen->addValue(      addBooleanValue(nodeMotions, "22", VALTYPE_MOTION, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeMotions, "23", VALTYPE_MOTION, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeMotions, "24", VALTYPE_MOTION, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeMotions, "25", VALTYPE_MOTION, ValueBase::VT_MID));
    egMainFloor->addValue(  addBooleanValue(nodeMotions, "26", VALTYPE_MOTION, ValueBase::VT_MID));
    egSideFloor->addValue(  addBooleanValue(nodeMotions, "27", VALTYPE_MOTION, ValueBase::VT_MID));

    // og
    sleepingRoom->addValue( addBooleanValue(nodeMotions, "40", VALTYPE_MOTION, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeMotions, "41", VALTYPE_MOTION, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeMotions, "42", VALTYPE_MOTION, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeMotions, "43", VALTYPE_MOTION, ValueBase::VT_MID));
    ogFloor->addValue(      addBooleanValue(nodeMotions, "44", VALTYPE_MOTION, ValueBase::VT_MID));
    ogMainFloor->addValue(  addBooleanValue(nodeMotions, "45", VALTYPE_MOTION, ValueBase::VT_MID));

    ValueGroup* nodePirs = addValueGroup("motions_pirs");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodePirs, "20", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodePirs, "21", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodePirs, "22", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    egMainFloor->addValue(    addBooleanValue(nodePirs, "23", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodePirs, "24", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodePirs, "25", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodePirs, "26", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodePirs, "40", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodePirs, "41", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodePirs, "42", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodePirs, "43", VALTYPE_MOTION_PIR, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodePirs, "44", VALTYPE_MOTION_PIR, ValueBase::VT_MID));

    ValueGroup* nodeRadars = addValueGroup("motions_radars");
    // basement
    //heatingRoom->addValue(  addBooleanValue(nodePirs, "0", VT_MOTION, ValueBase::VT_MID));
    // eg
    kitchen->addValue(      addBooleanValue(nodeRadars, "20", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    diningRoom->addValue(   addBooleanValue(nodeRadars, "21", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    toilet->addValue(       addBooleanValue(nodeRadars, "22", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    egMainFloor->addValue(    addBooleanValue(nodeRadars, "23", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    egFloor->addValue(      addBooleanValue(nodeRadars, "24", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    workingRoom->addValue(  addBooleanValue(nodeRadars, "25", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    supplyRoom->addValue(   addBooleanValue(nodeRadars, "26", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    // og
    ogFloor->addValue(      addBooleanValue(nodeRadars, "40", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    clothingRoom->addValue( addBooleanValue(nodeRadars, "41", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    livingRoom->addValue(   addBooleanValue(nodeRadars, "42", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    sleepingRoom->addValue( addBooleanValue(nodeRadars, "43", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));
    bathRoom->addValue(     addBooleanValue(nodeRadars, "44", VALTYPE_MOTION_RADAR, ValueBase::VT_MID));

    ValueGroup* nodeBrightnesses = addValueGroup("brightnesses");
    // eg
    kitchen->addValue(      addDoubleValue(nodeBrightnesses, "20", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    diningRoom->addValue(   addDoubleValue(nodeBrightnesses, "21", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    toilet->addValue(       addDoubleValue(nodeBrightnesses, "22", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
    egMainFloor->addValue(    addDoubleValue(nodeBrightnesses, "23", VALTYPE_BRIGHTNESS, ValueBase::VT_MID));
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
    kitchen->addActor(      addDigitalActor(nodeAlarms, "20", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    diningRoom->addActor(   addDigitalActor(nodeAlarms, "21", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    toilet->addActor(       addDigitalActor(nodeAlarms, "22", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    egMainFloor->addActor(    addDigitalActor(nodeAlarms, "23", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    egFloor->addActor(      addDigitalActor(nodeAlarms, "24", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    workingRoom->addActor(  addDigitalActor(nodeAlarms, "25", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    supplyRoom->addActor(   addDigitalActor(nodeAlarms, "26", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));

    ogFloor->addValue(      addDigitalActor(nodeBrightnesses, "40", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    clothingRoom->addValue( addDigitalActor(nodeBrightnesses, "41", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    livingRoom->addValue(   addDigitalActor(nodeBrightnesses, "42", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    sleepingRoom->addValue( addDigitalActor(nodeBrightnesses, "43", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));
    bathRoom->addValue(     addDigitalActor(nodeBrightnesses, "44", VALTYPE_ALARM_SOUND, ValueBase::VT_MID, true));

    ValueGroup* nodeWaterFlows = addValueGroup("waterFlows");
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "toilet", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "cold", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "warm", VALTYPE_WATER_FLOW, ValueBase::VT_MID));
    heatingRoom->addValue(addDoubleValue(nodeWaterFlows, "garden", VALTYPE_WATER_FLOW, ValueBase::VT_MID));

    ValueGroup* nodeWaterLevels = addValueGroup("waterLevels");
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "toilet", VALTYPE_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "cold", VALTYPE_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "warm", VALTYPE_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));
    heatingRoom->addValue(addIntegerValue(nodeWaterLevels, "garden", VALTYPE_WATER_LEVEL, ValueBase::VT_NONE)->withPersist(true));

    ValueGroup *nodeWbb12 = addValueGroup("wbb12");
    addValueActor(nodeWbb12, "hk1HeatingPauseParty", VALTYPE_HEAT_PUMP_DATA, ValueBase::VT_LONG, QVariant::Int);

    /*
    // test interval
    addProcessorTask("test", ProcessorTask::PTT_ONLY_ONCE, "CommonScripts.setupInterval('test', 1000, 5000, false)");
    addProcessorTask("test2", ProcessorTask::PTT_INTERVAL, "CommonScripts.getIntervalState('test')");
    */

    //addProcessorTask("eg.tempValve.kitchen", ProcessorTask::PTT_INTERVAL, "CommonScripts.applyTempValveLogic('temps.20', 'targetTemps.20', 'tempValves.20', 30000)", "", 1000);


    /*
    addProcessorTask("eg.motion.feg", ProcessorTask::PTT_INTERVAL, "CommonScripts.applyMotionLogic('motions_radars.24', 'motions_pirs.24', 'motions.24')", "", 500);
    addProcessorTask("eg.egFloor.light", ProcessorTask::PTT_INTERVAL, "CommonScripts.applySwitchMotionLogic('lightRelays.4', 'switches.24', 'motions.24', 'brightnesses.24', 20, 20000, 5000)");
    */

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


    // eg
    //addProcessorTask("Light", "eg.egFloor.light.init",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_ONLY_ONCE, "CommonScripts.initSwitchLogic('allRelays0.0', 'allSwitches0.0', 'lightToggles0.0')");
    //addProcessorTask("Light", "eg.egFloor.light",        ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchTimeoutLogic('lightToggles0.0', 10000)", "", 1000);

    /*
    addProcessorTask("eg.workingRoom.light",    ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.1', 'allSwitches0.1', 3600000)");
    addProcessorTask("eg.kitchen.light",        ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.2', 'allSwitches0.2', 3600000)");
    addProcessorTask("eg.diningRoom.light",     ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.3', 'allSwitches0.3', 3600000)");
    addProcessorTask("eg.toilet.light",         ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.4', 'allSwitches0.4', 3600000)");
    addProcessorTask("eg.supplyRoom.light",     ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.5', 'allSwitches0.5', 3600000)");
    addProcessorTask("eg.mainFloor.light",      ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.6', 'allSwitches0.6', 3600000)");
    //addProcessorTask("eg.tbd",                  ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.7', 'allSwitches0.7', 3600000)");

    // og
    addProcessorTask("og.sleepingRoom.light",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.16', 'allSwitches0.8', 3600000)");
    addProcessorTask("og.clothingRoom.light",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.17', 'allSwitches0.9', 3600000)");
    addProcessorTask("og.bathFloor.light",      ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.18', 'allSwitches0.10', 3600000)");
    addProcessorTask("og.livingRoom.light",     ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.19', 'allSwitches0.11', 3600000)");
    addProcessorTask("og.ogFloor.light",        ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.20', 'allSwitches0.12', 3600000)");
    addProcessorTask("og.tbd.light",            ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applySwitchLogic('allRelays0.21', 'allSwitches0.13', 3600000)");
    */


    // eg
    //addProcessorTask("Shutter", "eg.workingRoom.shutter",  ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.0', 'motions.21', 22, 0, 6, 0)", "", 120000);
    //addProcessorTask("Shutter", "eg.kitchen.shutter",      ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.1', 'motions.22', 22, 0, 6, 0)", "", 120000);
    //addProcessorTask("Shutter", "eg.diningRoom.shutter",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.2', 'motions.23', 22, 0, 6, 0)", "", 120000);
    //addProcessorTask("Shutter", "eg.toilet.shutter",       ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.3', 'motions.24', 22, 0, 6, 0)", "", 120000);
    //addProcessorTask("Shutter", "eg.supplyRoom.shutter",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.4', 'motions.25', 22, 0, 6, 0)", "", 120000);
    //addProcessorTask("Shutter", "eg.egSideFloor.shutter",  ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.5', 'motions.27', 22, 0, 6, 0)", "", 120000);

    /*
    // og
    addProcessorTask("og.sleepingRoom.shutter", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.6', 'motions.40', 22, 0, 6, 0)", "", 30000);
    addProcessorTask("og.clothingRoom.shutter", ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.7', 'motions.41', 22, 0, 6, 0)", "", 30000);
    addProcessorTask("og.bathFloor.shutter",    ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.8', 'motions.42', 22, 0, 6, 0)", "", 30000);
    addProcessorTask("og.livingRoom.shutter",   ProcessorTaskBase::PTT_NATIVE, ProcessorTaskBase::PTTT_INTERVAL, "CommonScripts.applyShutterLogic('allShutters0.9', 'motions.43', 22, 0, 6, 0)", "", 30000);
    */

    //addProcessorTask("logicproc1", "CommonScripts.ensureState(values_egRelays0_0, values_egInputs0_0, false, function(expected) {values_egRelays0_0.triggerCmd(expected ? C.ACTOR_CMD_ON : C.ACTOR_CMD_OFF )} );");
}
