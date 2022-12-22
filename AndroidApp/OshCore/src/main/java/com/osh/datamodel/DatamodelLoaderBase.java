package com.osh.datamodel;

import com.osh.Identifyable;

public abstract class DatamodelLoaderBase extends Identifyable {

	public DatamodelLoaderBase(String id) {
		super(id);
	}
	
    public abstract DatamodelBase load();

    public abstract void save(DatamodelBase datamodel);

    public abstract String typeName();


}
