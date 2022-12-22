package com.osh;

public class SerializableIdentifyable extends Identifyable {

	/*
	@JsonIgnore
	public static final String PROPERTY_CLASSTYPE = "classType";
	
	public final String classType;
	*/
	
	public SerializableIdentifyable(String id) {
		super(id);
		//classType = getClass().getSimpleName();
	}

	public SerializableIdentifyable() {
		super("");
		//classType = getClass().getSimpleName();
	}

}
