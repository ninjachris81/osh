package com.osh.datamodel;

import java.util.HashMap;
import java.util.Map;

import com.osh.SerializableIdentifyable;
import com.osh.SerializationSupport;
import com.osh.actor.ActorBase;
import com.osh.value.ValueBase;

public class KnownRoom extends SerializableIdentifyable implements SerializationSupport {
	
    private String name;
    
    private Map<String, ActorBase> actors = new HashMap<>();
    
	private Map<String, ValueBase> values = new HashMap<>();
    
    private ItemMetaInfo meta = new ItemMetaInfo();

	public KnownRoom(String id) {
		super(id);
	}

	public KnownRoom() {
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
	
}
