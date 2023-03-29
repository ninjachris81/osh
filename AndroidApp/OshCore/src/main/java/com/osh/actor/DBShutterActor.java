package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors_shutter")
public class DBShutterActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(uniqueCombo = true, columnName = "value_group_id")
    String valueGroupId;

    @DatabaseField(columnName = "shutter_tilt_support")
    boolean shutterTiltSupport;

    @DatabaseField(columnName = "shutter_full_close_duration")
    long shutterFullCloseDuration;

    @DatabaseField(columnName = "shutter_full_tilt_duration")
    long shutterFullTiltDuration;

    public String getId() {
        return id;
    }

    public String getValueGroupId() {
        return valueGroupId;
    }

    public boolean isShutterTiltSupport() {
        return shutterTiltSupport;
    }

    public long getShutterFullCloseDuration() {
        return shutterFullCloseDuration;
    }

    public long getShutterFullTiltDuration() {
        return shutterFullTiltDuration;
    }
}
