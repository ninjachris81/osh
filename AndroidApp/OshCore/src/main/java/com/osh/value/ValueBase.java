package com.osh.value;

import com.osh.SerializableIdentifyable;
import com.osh.datamodel.ItemMetaInfo;

public abstract class ValueBase extends SerializableIdentifyable {

	public enum VALUE_TIMEOUT {
		VT_NONE, VT_SHORT, VT_MID, VT_LONG
	};

	public static final String VALUE_SEPARATOR = ".";

	private VALUE_TIMEOUT valueTimeout = VALUE_TIMEOUT.VT_NONE;

	private ValueType valueType;

	
	private ItemMetaInfo meta = new ItemMetaInfo();

	private ValueGroup valueGroup;
	
	private boolean persistValue;

	protected Object value;
	
    double signalRate = 0;
    int signalCount = 0;
    long currentSignalCount = 0;

	
	long lastUpdate = 0;

	public ValueBase(ValueGroup valueGroup, String id, ValueType valueType) {
		super(id);
		this.valueGroup = valueGroup;
		this.valueType = valueType;
	}

	public ValueBase() {
	}

	public boolean isValid() {
		// TODO Auto-generated method stub
		return false;
	}

	public Object getValue() {
		return value;
	}

	public ValueType getValueType() {
		return valueType;
	}

	public ValueGroup getValueGroup() {
		return valueGroup;
	}

	public void setValueGroup(ValueGroup valueGroup) {
		this.valueGroup = valueGroup;
	}

	/*
	 * public void setValueGroup(String valueGroupId) { this.valueGroup = new
	 * ValueGroup(valueGroupId); }
	 */

	public ValueBase withValueTimeout(VALUE_TIMEOUT timeout) {
		this.valueTimeout = timeout;
		return this;
	}

	public VALUE_TIMEOUT getValueTimeout() {
		return valueTimeout;
	}

	public void setValueTimeout(VALUE_TIMEOUT valueTimeout) {
		this.valueTimeout = valueTimeout;
	}

	public String getFullId() {
		return getFullId(valueGroup.getId(), getId());
	}

	public static String getFullId(String valueGroupId, String valueId) {
		return valueGroupId + VALUE_SEPARATOR + valueId;
	}

	public ItemMetaInfo getMeta() {
		return meta;
	}

	public void setMeta(ItemMetaInfo meta) {
		this.meta = meta;
	}

	public boolean updateValue(Object newValue) {
	    currentSignalCount++;

	    boolean isDifferent = !value.equals(newValue);
	    //value = _updateValue(newValue);
	    //bool newValueApplied = m_value == newValue;
	    lastUpdate = System.currentTimeMillis();
	    return isDifferent;
	}

	public boolean isPersistValue() {
		return persistValue;
	}

	public void setPersistValue(boolean persistValue) {
		this.persistValue = persistValue;
	}
	
}
