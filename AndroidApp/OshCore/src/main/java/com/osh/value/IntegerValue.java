package com.osh.value;

import com.osh.SerializationSupport;

public class IntegerValue extends ValueBase implements SerializationSupport {

	public IntegerValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public IntegerValue() {
	}

}
