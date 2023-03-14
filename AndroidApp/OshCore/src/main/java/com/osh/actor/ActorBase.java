package com.osh.actor;

import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

import java.util.Map;

public abstract class ActorBase<VALUE_TYPE extends ActorBase, NATIVE_TYPE> extends ValueBase<VALUE_TYPE, NATIVE_TYPE> {

	protected Map<String, Object> config;
	public abstract boolean cmdSupported(ActorCmds cmd);
    protected abstract void _triggerCmd(ActorCmds cmd);

	public ActorBase(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public ActorBase() {
	}
	
	public void triggerCmd(ActorCmds cmd, String reason) {
	    if (cmdSupported(cmd)) {
	        _triggerCmd(cmd);
	    }
	}


}
