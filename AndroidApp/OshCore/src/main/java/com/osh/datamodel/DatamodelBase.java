package com.osh.datamodel;

import java.util.HashMap;
import java.util.Map;

import com.osh.Identifyable;
import com.osh.actor.ActorBase;
import com.osh.actor.DigitalActor;
import com.osh.device.KnownDevice;
import com.osh.processor.ProcessorTask;
import com.osh.value.BooleanValue;
import com.osh.value.DoubleValue;
import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class DatamodelBase extends Identifyable {
	
	protected Map<String, ValueGroup> valueGroups = new HashMap<>();
	
	protected Map<String, KnownDevice> knownDevices = new HashMap<>();
	
	protected Map<String, KnownRoom> knownRooms = new HashMap<>();

	protected Map<String, ValueBase> values = new HashMap<>();
	
    protected Map<String, ActorBase> actors = new HashMap<>();

    protected Map<String, ProcessorTask> processorTasks = new HashMap<>();

	public DatamodelBase(String id) {
		super(id);
	}

	public Map<String, KnownDevice> getKnownDevices() {
		return knownDevices;
	}

	public Map<String, ValueGroup> getValueGroups() {
		return valueGroups;
	}

	public Map<String, ValueBase> getValues() {
		return values;
	}

	public Map<String, ActorBase> getActors() {
		return actors;
	}

	public Map<String, KnownRoom> getKnownRooms() {
		return knownRooms;
	}

	public Map<String, ProcessorTask> getProcessorTasks() {
		return processorTasks;
	}
	
	public KnownDevice addKnownDevice(String id, String serviceId, String name) {
	    KnownDevice device = new KnownDevice(id, serviceId, name);
	    knownDevices.put(device.getFullId(), device);
	    return device;
	}
	
	public ValueGroup addValueGroup(String id) {
	    ValueGroup valueGroup = new ValueGroup(id);
	    valueGroups.put(valueGroup.getId(), valueGroup);
	    return valueGroup;
	}
	
	public DigitalActor addDigitalActor(ValueGroup valueGroup, String id, ValueType valueType, boolean isAsync, ValueBase.VALUE_TIMEOUT timeout) {
	    DigitalActor actor = new DigitalActor(valueGroup, id, valueType, isAsync);
	    actor.withValueTimeout(timeout);
	    actors.put(actor.getId(), actor);
	    return actor;
	}
	
	public BooleanValue addBooleanValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
	    BooleanValue value = new BooleanValue(valueGroup, id, valueType);
	    value.withValueTimeout(timeout);
	    values.put(value.getId(), value);
	    return value;
	}
	
	public DoubleValue addDoubleValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
	    DoubleValue value = new DoubleValue(valueGroup, id, valueType);
	    value.withValueTimeout(timeout);
	    values.put(value.getId(), value);
	    return value;
	}
	
	public ValueBase addValue(ValueBase value) {
	    values.put(value.getId(), value);
	    return value;
	}

	
	public ProcessorTask addProcessorTask(String id, ProcessorTask.ProcessorTaskType taskType, String scriptCode, String runCondition, long scheduleInterval) {
	    ProcessorTask processorNode = new ProcessorTask(id, taskType, scriptCode, runCondition, scheduleInterval);
	    processorTasks.put(processorNode.getId(), processorNode);
	    return processorNode;
	}	

	public KnownRoom addKnownRoom(String id, String name) {
	    KnownRoom knownRoom = new KnownRoom(id);
	    knownRoom.setName(name);
	    knownRooms.put(knownRoom.getId(), knownRoom);
	    return knownRoom;
	}

}
