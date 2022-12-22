package com.osh.datamodel;

public class HttpDatamodelLoader extends DatamodelLoaderBase {

	public static final String LOADER_TYPE_NAME = "http";
	private final String url;
	
	public HttpDatamodelLoader(String url) {
		super("HttpDatamodelLoader");
		this.url = url;
	}

	@Override
	public DatamodelBase load() {
		// TODO Auto-generated method stub
		return null;
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
