package com.osh.value;

import java.util.Map;

import com.osh.communication.MessageBase;
import com.osh.communication.mqtt.MqttConstants;

public class ValueMessage extends MessageBase {
	
    private String valueGroupId;
    private String valueId;
    private Object rawValue;

	public ValueMessage(String valueGroupId, String valueId, Object rawValue) {
		this.valueGroupId = valueGroupId;
		this.valueId = valueId;
		this.rawValue = rawValue;
	}

	public ValueMessage(String valueGroupId, String valueId, Map<String, Object> value) {
		this.valueGroupId = valueGroupId;
		this.valueId = valueId;
	    if (value.containsKey(MqttConstants.MQTT_SINGLE_VALUE_ATTR)) {
	        rawValue = value.get(MqttConstants.MQTT_SINGLE_VALUE_ATTR);
	    }
	}

	public ValueMessage(ValueBase value) {
		this(value.getValueGroup().getId(), value.getId(), value.getValue());
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_VALUE;
	}

	@Override
	public String getFirstLevelId() {
		return valueGroupId;
	}

	@Override
	public String getSecondLevelId() {
		return valueId;
	}

	public String getValueGroupId() {
		return valueGroupId;
	}

	public String getValueId() {
		return valueId;
	}

	public Object getRawValue() {
		return rawValue;
	}

	public String getFullId() {
		return ValueBase.getFullId(valueGroupId, valueId);
	}
	
}
