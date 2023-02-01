package com.osh.datamodel;

import java.util.HashSet;
import java.util.Set;

import com.osh.Identifyable;
import com.osh.actor.ActorBase;
import com.osh.value.ValueBase;

public class DatamodelView extends Identifyable {

	protected Set<ValueBase> values = new HashSet<>();

    protected Set<ActorBase> actors = new HashSet<>();
	
	protected DatamodelView() {
		super("");
	}
	
	public DatamodelView(String id) {
		super(id);
	}

	public Set<ValueBase> getValues() {
		return values;
	}

	public void setValues(Set<ValueBase> values) {
		this.values = values;
	}

	public Set<ActorBase> getActors() {
		return actors;
	}

	public void setActors(Set<ActorBase> actors) {
		this.actors = actors;
	}
	
}
