package com.osh.datamodel.meta;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_known_rooms_values")
public class KnownRoomValues {

    @DatabaseField(columnName = "room_id")
    String roomId;

    @DatabaseField(columnName = "value_id")
    String valueId;

    @DatabaseField(columnName = "value_group_id")
    String valueGroupId;

    public String getRoomId() {
        return roomId;
    }

    public String getValueId() {
        return valueId;
    }

    public String getValueGroupId() {
        return valueGroupId;
    }
}
