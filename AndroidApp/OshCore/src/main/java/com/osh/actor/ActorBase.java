package com.osh.actor;

import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public abstract class ActorBase extends ValueBase {
	
	public abstract boolean cmdSupported(ActorCmds cmd);
    protected abstract void _triggerCmd(ActorCmds cmd);

	public ActorBase(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	public ActorBase() {
	}
	
	void triggerCmd(ActorCmds cmd, String reason) {
	    if (cmdSupported(cmd)) {
	        _triggerCmd(cmd);
	    }
	}

	
}
