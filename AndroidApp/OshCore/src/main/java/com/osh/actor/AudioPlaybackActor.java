package com.osh.actor;

import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class AudioPlaybackActor extends ActorBase {

	private final String audioDeviceIds;

	private final String audioActivationRelayId;

	private final float audioVolume;

	private final String audioVolumeId;

	private final String audioDefaultUrl;

	public AudioPlaybackActor(ValueGroup valueGroup, String id, ValueType valueType, String audioDeviceIds, String audioActivationRelayId, float audioVolume, String audioVolumeId, String audioDefaultUrl) {
		super(valueGroup, id, valueType);
		this.audioDeviceIds = audioDeviceIds;
		this.audioActivationRelayId = audioActivationRelayId;
		this.audioVolume = audioVolume;
		this.audioVolumeId = audioVolumeId;
		this.audioDefaultUrl = audioDefaultUrl;
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
