package com.osh.actor;

import com.osh.utils.ObservableDouble;
import com.osh.utils.ObservableString;
import com.osh.value.DoubleValue;
import com.osh.value.StringValue;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class AudioPlaybackActor extends ActorBase {

	private final String audioDeviceIds;

	private final String audioActivationRelayId;

	private final ObservableDouble audioVolume;

	private DoubleValue audioVolumeValue;
	private final String audioVolumeId;

	private final ObservableString audioUrl;
	private StringValue audioUrlValue;
	private final String audioUrlId;

	public AudioPlaybackActor(ValueGroup valueGroup, String id, ValueType valueType, String audioDeviceIds, String audioActivationRelayId, float audioVolume, String audioVolumeId, String audioUrl, String audioUrlId) {
		super(valueGroup, id, valueType);
		this.audioDeviceIds = audioDeviceIds;
		this.audioActivationRelayId = audioActivationRelayId;
		this.audioVolume = new ObservableDouble((double) audioVolume);
		this.audioVolumeId = audioVolumeId;
		this.audioUrl = new ObservableString(audioUrl);
		this.audioUrlId = audioUrlId;
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

	public String getAudioDeviceIds() {
		return audioDeviceIds;
	}

	public String getAudioActivationRelayId() {
		return audioActivationRelayId;
	}

	public ObservableDouble getAudioVolume() {
		return audioVolume;
	}

	public String getAudioVolumeId() {
		return audioVolumeId;
	}

	public ObservableString getAudioUrl() {
		return audioUrl;
	}

	public String getAudioUrlId() {
		return audioUrlId;
	}

	public void setVolumeValue(DoubleValue volume) {
		this.audioVolumeValue = volume;
		audioVolumeValue.addItemChangeListener(item -> {
			audioVolume.changeValue(item.getValue());
		});
	}

	public void setUrlValue(StringValue url) {
		this.audioUrlValue = url;
		audioUrlValue.addItemChangeListener(item -> {
			audioUrl.changeValue(item.getValue());
		});
	}
}
