package com.osh.actor;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_actors")
public class DBActor {

    @DatabaseField(uniqueCombo = true)
    String id;

    @DatabaseField(canBeNull = false, columnName = "class_type")
    String classType;

    @DatabaseField(uniqueCombo = true, columnName = "value_group_id")
    String valueGroupId;

    @DatabaseField(columnName = "value_type")
    int valueType;

    @DatabaseField(columnName = "value_timeout")
    int valueTimeout;

    @DatabaseField(columnName = "is_async")
    boolean isAsync;

    @DatabaseField
    String comment;

    public String getId() {
        return id;
    }

    public String getClassType() {
        return classType;
    }

    public String getValueGroupId() {
        return valueGroupId;
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

    public String getComment() {
        return comment;
    }
}
