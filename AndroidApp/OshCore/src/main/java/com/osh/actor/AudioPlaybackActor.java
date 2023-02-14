package com.osh.actor;

import com.osh.SerializationSupport;

public class AudioPlaybackActor extends ActorBase implements SerializationSupport {

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
