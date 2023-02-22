package com.osh.actor;

import com.osh.SerializationSupport;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class DigitalActor extends ActorBase implements SerializationSupport {
	
	protected boolean isAsync;

	public DigitalActor(ValueGroup valueGroup, String id, ValueType valueType, boolean isAsync) {
		super(valueGroup, id, valueType);
		this.isAsync = isAsync;
	}

	public DigitalActor() {
		super();
	}

	@Override
	public boolean cmdSupported(ActorCmds cmd) {
	    switch(cmd) {
	    case ACTOR_CMD_ON:
	    case ACTOR_CMD_OFF:
	        return true;
	    default:
	        return false;
	    }
	}

	@Override
	protected void _triggerCmd(ActorCmds cmd) {
	    switch(cmd) {
	    case ACTOR_CMD_ON:
	        //Q_EMIT(statusRequested(true));
	        break;
	    case ACTOR_CMD_OFF:
	        //Q_EMIT(statusRequested(false));o
	        break;
	    default:
	        break;
	    }
	}
	
	protected Object _updateValue(Object newValue) {
	    if (newValue instanceof Boolean) {
	        return newValue;
	    } else {
	        return null;
	    }
	}

}
