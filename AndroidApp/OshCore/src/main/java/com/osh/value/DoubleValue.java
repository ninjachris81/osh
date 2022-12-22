package com.osh.value;

import com.osh.SerializationSupport;

public class DoubleValue extends ValueBase implements SerializationSupport {

	public DoubleValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public DoubleValue() {
	}

}
