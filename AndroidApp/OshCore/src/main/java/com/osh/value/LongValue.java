package com.osh.value;

import com.osh.SerializationSupport;

public class LongValue extends ValueBase implements SerializationSupport {

	public LongValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public LongValue() {
	}

}