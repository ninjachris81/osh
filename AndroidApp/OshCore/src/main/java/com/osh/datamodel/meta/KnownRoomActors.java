package com.osh.datamodel.meta;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_known_rooms_actors")
public class KnownRoomActors {

    @DatabaseField(columnName = "room_id")
    String roomId;

    @DatabaseField(columnName = "actor_id")
    String actorId;

    @DatabaseField(columnName = "value_group_id")
    String valueGroupId;

    public String getRoomId() {
        return roomId;
    }

    public String getActorId() {
        return actorId;
    }

    public String getValueGroupId() {
        return valueGroupId;
    }
}
