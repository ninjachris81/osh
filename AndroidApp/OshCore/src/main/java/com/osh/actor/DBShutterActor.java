package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors_shutter")
public class DBShutterActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(uniqueCombo = true)
    String valueGroupId;

    @DatabaseField
    boolean shutterTiltSupport;

    @DatabaseField
    long shutterFullCloseDuration;

    @DatabaseField
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
