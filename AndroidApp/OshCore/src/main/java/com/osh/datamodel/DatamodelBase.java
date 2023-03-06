package com.osh.datamodel;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.osh.Identifyable;
import com.osh.actor.ActorBase;
import com.osh.actor.DigitalActor;
import com.osh.actor.ShutterActor;
import com.osh.actor.ToggleActor;
import com.osh.actor.ValueActor;
import com.osh.datamodel.meta.KnownArea;
import com.osh.datamodel.meta.KnownRoom;
import com.osh.device.KnownDevice;
import com.osh.processor.ProcessorTask;
import com.osh.value.BooleanValue;
import com.osh.value.DoubleValue;
import com.osh.value.IntegerValue;
import com.osh.value.LongValue;
import com.osh.value.StringValue;
import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class DatamodelBase extends Identifyable {
	
	protected Map<String, ValueGroup> valueGroups = new HashMap<>();
	
	protected Map<String, KnownDevice> knownDevices = new HashMap<>();
	
	protected Map<String, KnownRoom> knownRooms = new HashMap<>();

	protected Map<String, KnownArea> knownAreas = new HashMap<>();

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
	
	public DigitalActor addDigitalActor(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout, boolean isAsync) {
	    DigitalActor actor = new DigitalActor(valueGroup, id, valueType, isAsync);
	    actor.withValueTimeout(timeout);
	    actors.put(actor.getFullId(), actor);
	    return actor;
	}
	public ShutterActor addShutterActor(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout, boolean tiltSupport, int fullCloseDuration) {
		ShutterActor actor = new ShutterActor(valueGroup, id, valueType);
		actor.withValueTimeout(timeout);
		actors.put(actor.getFullId(), actor);
		return actor;
	}

	public ToggleActor addToggleActor(ValueGroup valueGroup, String id) {
		ToggleActor actor = new ToggleActor(valueGroup, id);
		actors.put(actor.getFullId(), actor);
		return actor;
	}

	public ValueActor addValueActor(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
		ValueActor actor = new ValueActor(valueGroup, id, valueType);
		actor.withValueTimeout(timeout);
		actors.put(actor.getFullId(), actor);
		return actor;
	}


	public BooleanValue addBooleanValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
	    BooleanValue value = new BooleanValue(valueGroup, id, valueType);
	    value.withValueTimeout(timeout);
	    values.put(value.getFullId(), value);
	    return value;
	}
	
	public DoubleValue addDoubleValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
	    DoubleValue value = new DoubleValue(valueGroup, id, valueType);
	    value.withValueTimeout(timeout);
	    values.put(value.getFullId(), value);
	    return value;
	}

	public IntegerValue addIntegerValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
		IntegerValue value = new IntegerValue(valueGroup, id, valueType);
		value.withValueTimeout(timeout);
		values.put(value.getFullId(), value);
		return value;
	}

	public LongValue addLongValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
		LongValue value = new LongValue(valueGroup, id, valueType);
		value.withValueTimeout(timeout);
		values.put(value.getFullId(), value);
		return value;
	}

	public StringValue addStringValue(ValueGroup valueGroup, String id, ValueType valueType, ValueBase.VALUE_TIMEOUT timeout) {
		StringValue value = new StringValue(valueGroup, id, valueType);
		value.withValueTimeout(timeout);
		values.put(value.getFullId(), value);
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

	public KnownRoom addKnownRoom(KnownArea knownArea, String id, String name) {
	    KnownRoom knownRoom = new KnownRoom(id, name);
		knownRoom.setKnownArea(knownArea);
	    knownRooms.put(knownRoom.getId(), knownRoom);
	    return knownRoom;
	}

	public ValueGroup getValueGroup(String valueGroup) {
		return valueGroups.get(valueGroup);
	}


	public KnownArea addKnownArea(String id, String name) {
		KnownArea knownArea = new KnownArea(id, name);
		knownAreas.put(knownArea.getId(), knownArea);
		return knownArea;
	}

	public KnownArea getKnownArea(String knownArea) {
		return knownAreas.get(knownArea);
	}

	public KnownRoom getKnownRoom(String roomId) {
		return knownRooms.get(roomId);
	}

	public ValueBase getValue(String valueId, String valueGroupId) {
		return values.get(ValueBase.getFullId(valueGroupId, valueId));
	}

	public ActorBase getActor(String actorId, String valueGroupId) {
		return actors.get(ValueBase.getFullId(valueGroupId, actorId));
	}

    public List<KnownArea> getKnownAreas() {
		List<KnownArea> ka = new ArrayList(knownAreas.values());
		Collections.sort(ka, Comparator.comparingInt(KnownArea::getDisplayOrder));
		return ka;
    }

}
