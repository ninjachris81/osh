package com.osh.datamodel.meta;

import java.util.HashMap;
import java.util.Map;

import com.j256.ormlite.field.DatabaseField;
import com.j256.ormlite.table.DatabaseTable;
import com.osh.SerializableIdentifyable;
import com.osh.SerializationSupport;
import com.osh.actor.ActorBase;
import com.osh.datamodel.ItemMetaInfo;
import com.osh.value.ValueBase;

@DatabaseTable(tableName = "dm_known_rooms")
public class KnownRoom {

	@DatabaseField(id = true)
	private String id;
    @DatabaseField(canBeNull = false)
	private String name;

	@DatabaseField(canBeNull = false, columnName = "knownArea")
	private String knownAreaString;
	private KnownArea knownArea;

    private Map<String, ActorBase> actors = new HashMap<>();
    
	private Map<String, ValueBase> values = new HashMap<>();
    
    private ItemMetaInfo meta = new ItemMetaInfo();

	protected KnownRoom() {
	}

	public KnownRoom(String id, String name) {
		this.id = id;
		this.name = name;
	}

	public String getId() {
		return id;
	}

	public String getKnownAreaString() {
		return knownAreaString;
	}

	public KnownArea getKnownArea() {
		return knownArea;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}
	
	public Map<String, ActorBase> getActors() {
		return actors;
	}

	public void setActors(Map<String, ActorBase> actors) {
		this.actors = actors;
	}

	public Map<String, ValueBase> getValues() {
		return values;
	}

	public void setValues(Map<String, ValueBase> values) {
		this.values = values;
	}

	public ItemMetaInfo getMeta() {
		return meta;
	}

	public void setMeta(ItemMetaInfo meta) {
		this.meta = meta;
	}

	public void setKnownArea(KnownArea knownArea) {
		this.knownArea = knownArea;
	}

	public void addValue(ValueBase value) {
		this.values.put(value.getFullId(), value);
	}

	public void addActor(ActorBase actor) {
		this.actors.put(actor.getFullId(), actor);
	}
}
