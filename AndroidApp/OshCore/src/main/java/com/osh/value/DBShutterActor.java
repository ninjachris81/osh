package com.osh.value;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors_shutter")
public class DBShutterActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(uniqueCombo = true)
    String valueGroup;

    @DatabaseField
    boolean shutterTiltSupport;

    @DatabaseField
    long shutterFullCloseDuration;

    @DatabaseField
    long shutterFullTiltDuration;

    public String getId() {
        return id;
    }

    public String getValueGroup() {
        return valueGroup;
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
