package com.osh.value;

import com.osh.SerializationSupport;

public class StringValue extends ValueBase<StringValue, String> implements SerializationSupport {

	@Override
	protected String _updateValue(Object newValue) {
		if (newValue instanceof String) {
			return (String) newValue;
		} else if (newValue instanceof Number) {
			return ((Number) newValue).toString();
		} else if (newValue instanceof Boolean) {
			return ((Boolean) newValue).toString();
		} else {
			return null;
		}
	}

	public StringValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public StringValue() {
	}

}
