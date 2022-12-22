package com.osh.datamodel;

public class TestDatamodel extends DatamodelBase {

	public TestDatamodel() {
		super("TestDatamodel");
		
	    addKnownDevice("349785676", "CoreServer", "Server");
	    addKnownDevice("582645258", "CoreUI", "GUI");
	    addKnownDevice("66403375", "InputService", "Node EG Input");
	    addKnownDevice("66403375", "RelayService", "Node EG Relay");
	    addKnownDevice("0020", "SensorService_20", "Sensor EG Kueche");

	    // ROOMS
	    // BASEMENT
	    KnownRoom heatingRoom = addKnownRoom("heatingRoom", "Heizraum");
	    KnownRoom workshop = addKnownRoom("workshop", "Werkstatt");
	    KnownRoom basementFloor0 = addKnownRoom("basementFloor0", "HF");
	    KnownRoom basementFloor1 = addKnownRoom("basementFloor1", "Flur");
	    KnownRoom storage1 = addKnownRoom("storage1", "L1");
	    KnownRoom storage2 = addKnownRoom("storage2", "L2");
	    KnownRoom storage3 = addKnownRoom("storage3", "L3");

	    // EG
	    KnownRoom kitchen = addKnownRoom("kitchen", "K�che");
	    KnownRoom diningRoom = addKnownRoom("diningRoom", "EZ");
	    KnownRoom toilet = addKnownRoom("toilet", "WC");
	    KnownRoom mainFloor = addKnownRoom("mainFloor", "HF");
	    KnownRoom egFloor = addKnownRoom("egFloor", "Flur");
	    KnownRoom workingRoom = addKnownRoom("workingRoom", "AZ");
	    KnownRoom supplyRoom = addKnownRoom("supplyRoom", "VZ");
	    // OG
	    KnownRoom ogFloor = addKnownRoom("ogFloor", "Flur");
	    KnownRoom clothingRoom = addKnownRoom("clothingRoom", "AZ");
	    KnownRoom livingRoom = addKnownRoom("livingRoom", "WZ");
	    KnownRoom sleepingRoom = addKnownRoom("sleepingRoom", "SZ");
	    KnownRoom bathRoom = addKnownRoom("bathRoom", "Bad");
	}

}
