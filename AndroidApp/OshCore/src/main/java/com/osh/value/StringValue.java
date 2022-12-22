package com.osh.value;

import com.osh.SerializationSupport;

public class StringValue extends ValueBase implements SerializationSupport {

	public StringValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public StringValue() {
	}

}
