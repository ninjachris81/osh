package com.osh.datamodel;

public class TestDatamodelLoader extends DatamodelLoaderBase {

	public static final String LOADER_TYPE_NAME = "test";

	public TestDatamodelLoader() {
		super("TestDatamodelLoader");
	}

	@Override
	public DatamodelBase load() {
		return new TestDatamodel();
	}

	@Override
	public void save(DatamodelBase datamodel) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public String typeName() {
		return LOADER_TYPE_NAME;
	}

}
