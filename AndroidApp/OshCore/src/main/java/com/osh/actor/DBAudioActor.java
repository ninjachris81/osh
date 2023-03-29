package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors_audio")
public class DBAudioActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(uniqueCombo = true, columnName = "value_group_id")
    String valueGroupId;

    @DatabaseField(columnName = "audio_device_ids")
    String audioDeviceIds;

    @DatabaseField(columnName = "audio_activation_relay_id")
    String audioActivationRelayId;

    @DatabaseField(columnName = "audio_volume")
    float audioVolume;

    @DatabaseField(columnName = "audio_volume_id")
    String audioVolumeId;

    @DatabaseField(columnName = "audio_url")
    String audioUrl;

    @DatabaseField(columnName = "audio_url_id")
    String audioUrlId;

    public String getId() {
        return id;
    }

    public String getValueGroupId() {
        return valueGroupId;
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

    public String getAudioUrl() {
        return audioUrl;
    }

    public String getAudioUrlId() {
        return audioUrlId;
    }
}
