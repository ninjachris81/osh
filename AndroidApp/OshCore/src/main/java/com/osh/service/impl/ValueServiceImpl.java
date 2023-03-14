package com.osh.service.impl;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.service.ICommunicationService;
import com.osh.service.IValueService;
import com.osh.utils.IObservableManager;
import com.osh.utils.ObservableManagerImpl;
import com.osh.value.ValueBase;
import com.osh.value.ValueMessage;

public class ValueServiceImpl implements IValueService {
	
	private static final Logger log = LoggerFactory.getLogger(ValueServiceImpl.class);

	protected final Map<String, ValueBase> values = new HashMap<>();

	protected final IObservableManager observableManager = new ObservableManagerImpl();

	protected final ICommunicationService communicationService;

	public ValueServiceImpl(ICommunicationService communicationService) {
		this.communicationService = communicationService;
		communicationService.registerMessageType(getMessageType(), this);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_VALUE;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
		if (msg instanceof ValueMessage) {
			log.info("Value received {}", msg);
			
			valueReceived(((ValueMessage)msg).getValueGroupId(), ((ValueMessage)msg).getValueId(), ((ValueMessage)msg).getRawValue());
		}
	}

	private void valueReceived(String valueGroupId, String valueId, Object newValue) {
	    ValueBase value = getValue(valueGroupId, valueId);
	    if (value != null) {
	        valueReceived(value, newValue);
	    } else {
	        log.warn("Value not registered {}.{}", valueGroupId, valueId);
	    }
	}

	private void valueReceived(ValueBase value, Object newValue) {
	    if (value != null) {
	        value.updateValue(newValue);
	        if (value.isPersistValue()) {
	        	// TODO
	            //m_databaseManager->simpleSet(VALUE_PREFIX, value->fullId(), value->rawValue());
	        }
	    }
	}

	private ValueBase getValue(String valueGroupId, String valueId) {
	    return getValue(ValueBase.getFullId(valueGroupId, valueId));
	}

	@Override
	public ValueBase getValue(String fullId) {
	    if (values.containsKey(fullId)) {
	        return values.get(fullId);
	    } else {
	        return null;
	    }
	}

	@Override
	public void registerValue(ValueBase value) {
		values.put(value.getFullId(), value);
	}

	@Override
	public void publishValue(ValueBase value) {
		ValueMessage msg = new ValueMessage(value);
		communicationService.sendMessage(msg);

	}

}
