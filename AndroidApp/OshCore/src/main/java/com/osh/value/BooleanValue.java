package com.osh.value;

import com.osh.SerializationSupport;

public class BooleanValue extends ValueBase implements SerializationSupport {

	public BooleanValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public BooleanValue() {
		super();
	}

}
