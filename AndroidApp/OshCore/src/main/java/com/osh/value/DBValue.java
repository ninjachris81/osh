package com.osh.value;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_values")
public class DBValue {

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

    @DatabaseField
    String comment;

    @DatabaseField(columnName = "enum_count")
    int enumCount;

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

    public String getComment() {
        return comment;
    }

    public int getEnumCount() {
        return enumCount;
    }
}
