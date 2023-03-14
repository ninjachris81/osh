package com.osh.datamodel.meta;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;

@DatabaseTable(tableName = "dm_known_rooms_actors")
public class KnownRoomActors {

    @DatabaseField
    String roomId;

    @DatabaseField
    String actorId;

    @DatabaseField
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
