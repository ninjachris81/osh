package com.osh.value;

public interface IValueManager {

	void registerValue(ValueBase valueBase);

	ValueBase getValue(String fullId);

}
