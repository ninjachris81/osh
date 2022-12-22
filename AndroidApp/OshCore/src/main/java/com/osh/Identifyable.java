package com.osh;

public abstract class Identifyable {

	public final String PROPERTY_ID = "id";

	protected String id;

	public Identifyable(String id) {
		this.id = id;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}
	
}
