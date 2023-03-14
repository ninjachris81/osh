package com.osh.actor;

import com.osh.SerializationSupport;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class AudioPlaybackActor extends ActorBase {

	public AudioPlaybackActor(ValueGroup valueGroup, String id, ValueType valueType) {
		super(valueGroup, id, valueType);
	}

	@Override
	public boolean cmdSupported(ActorCmds cmd) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	protected void _triggerCmd(ActorCmds cmd) {
		// TODO Auto-generated method stub
		
	}

	@Override
	protected Object _updateValue(Object newValue) {
		return newValue;
	}
}
