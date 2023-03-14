package com.osh.datamodel.meta;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;
import com.osh.actor.ActorBase;
import com.osh.datamodel.ItemMetaInfo;
import com.osh.value.ValueBase;

import java.util.HashMap;
import java.util.Map;

@DatabaseTable(tableName = "dm_known_areas")
public class KnownArea {

    @DatabaseField(id = true)
    private String id;
    @DatabaseField(canBeNull = false)
    private String name;

    @DatabaseField
    private int displayOrder;

    private Map<String, ActorBase> actors = new HashMap<>();

    private Map<String, ValueBase> values = new HashMap<>();

    private ItemMetaInfo meta = new ItemMetaInfo();

    protected KnownArea() {
    }

    public KnownArea(String id, String name) {
        this.id = id;
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public int getDisplayOrder() {
        return displayOrder;
    }
}
