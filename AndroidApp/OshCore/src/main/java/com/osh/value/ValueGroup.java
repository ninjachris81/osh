package com.osh.value;

import com.osh.SerializableIdentifyable;
import com.osh.SerializationSupport;

public class ValueGroup extends SerializableIdentifyable implements SerializationSupport {

	public ValueGroup(String id) {
		super(id);
	}

	public ValueGroup() {
		super();
	}

}
