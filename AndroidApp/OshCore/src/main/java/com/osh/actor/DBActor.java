package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;
import com.osh.value.ValueGroup;

@DatabaseTable(tableName = "dm_actors")
public class DBActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(canBeNull = false)
    String classType;

    @DatabaseField(uniqueCombo = true)
    String valueGroup;

    @DatabaseField
    int valueType;

    @DatabaseField
    int valueTimeout;

    @DatabaseField
    boolean isAsync;

    @DatabaseField
    boolean tiltSupport;

    @DatabaseField
    int fullCloseDuration;

    @DatabaseField
    String comment;

    public String getId() {
        return id;
    }

    public String getClassType() {
        return classType;
    }

    public String getValueGroup() {
        return valueGroup;
    }

    public int getValueType() {
        return valueType;
    }

    public int getValueTimeout() {
        return valueTimeout;
    }

    public boolean isAsync() {
        return isAsync;
    }

    public boolean isTiltSupport() {
        return tiltSupport;
    }

    public int getFullCloseDuration() {
        return fullCloseDuration;
    }

    public String getComment() {
        return comment;
    }
}
