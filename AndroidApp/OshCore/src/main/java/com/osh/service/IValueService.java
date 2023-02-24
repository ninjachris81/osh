package com.osh.service;

import com.osh.manager.IMqttSupport;
import com.osh.value.ValueBase;

public interface IValueService extends IMqttSupport {

	void registerValue(ValueBase valueBase);

	ValueBase getValue(String fullId);

    void publishValue(ValueBase value);
}
