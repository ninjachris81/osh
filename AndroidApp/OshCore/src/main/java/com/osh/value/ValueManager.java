package com.osh.value;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;
import com.osh.manager.ManagerRegistration.INSTANCE_ROLE;

public class ValueManager extends ManagerBase implements IValueManager {
	
	private static final Logger log = LoggerFactory.getLogger(ValueManager.class);

	protected Map<String, ValueBase> values = new HashMap<>();

	public ValueManager(IManagerRegistration managerRegistration) {
		super("ValueManager", managerRegistration);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_VALUE;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
		if (msg instanceof ValueMessage) {
			log.info("Value received {}", msg);
			
			if (managerRegistration.getInstanceRole() == INSTANCE_ROLE.SERVER) {
				valueReceived(((ValueMessage)msg).getValueGroupId(), ((ValueMessage)msg).getValueId(), ((ValueMessage)msg).getRawValue());
			} else {
				
			}
		}
	}

	@Override
	public void initComplete() {

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

	private ValueBase getValue(String fullId) {
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
}
