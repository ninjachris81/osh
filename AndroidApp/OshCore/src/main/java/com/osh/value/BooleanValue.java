package com.osh.value;

import com.osh.SerializationSupport;

public class BooleanValue extends ValueBase<BooleanValue, Boolean> implements SerializationSupport {

	@Override
	protected Boolean _updateValue(Object newValue) {
		if (newValue instanceof Boolean) {
			return (Boolean) newValue;
		} else if (newValue instanceof Number) {
			return ((Number) newValue).intValue() == 1;
		} else if (newValue instanceof String) {
			return Boolean.getBoolean((String) newValue);
		} else {
			return null;
		}
	}

	public BooleanValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public BooleanValue() {
		super();
	}

}
