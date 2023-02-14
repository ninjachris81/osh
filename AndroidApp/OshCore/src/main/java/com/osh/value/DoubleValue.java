package com.osh.value;

import com.osh.SerializationSupport;

import org.apache.commons.lang3.math.NumberUtils;

public class DoubleValue extends ValueBase<DoubleValue, Double> implements SerializationSupport {

	@Override
	protected Double _updateValue(Object newValue) {
		if (newValue instanceof Double) {
			return (Double) newValue;
		} else if (newValue instanceof Number) {
			return ((Number) newValue).doubleValue();
		} else if (newValue instanceof String) {
			return Double.parseDouble((String) newValue);
		} else {
			return null;
		}
	}

	public DoubleValue(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public DoubleValue() {
	}

}
