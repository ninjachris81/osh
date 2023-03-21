package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors_audio")
public class DBAudioActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(uniqueCombo = true)
    String valueGroup;

    @DatabaseField
    String audioDeviceIds;

    @DatabaseField
    String audioActivationRelayId;

    @DatabaseField
    float audioVolume;

    @DatabaseField
    String audioVolumeId;

    @DatabaseField
    String audioDefaultUrl;

    public String getId() {
        return id;
    }

    public String getValueGroup() {
        return valueGroup;
    }

    public String getAudioDeviceIds() {
        return audioDeviceIds;
    }

    public String getAudioActivationRelayId() {
        return audioActivationRelayId;
    }

    public float getAudioVolume() {
        return audioVolume;
    }

    public String getAudioVolumeId() {
        return audioVolumeId;
    }

    public String getAudioDefaultUrl() {
        return audioDefaultUrl;
    }
}
