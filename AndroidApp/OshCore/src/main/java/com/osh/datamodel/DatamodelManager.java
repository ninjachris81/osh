package com.osh.datamodel;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.osh.actor.IActorManager;
import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.config.ApplicationConfig;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;
import com.osh.service.IDatamodelService;
import com.osh.value.IValueManager;

public class DatamodelManager extends ManagerBase implements IDatamodelManager {

	private static final Logger log = LoggerFactory.getLogger(DatamodelManager.class);

    private DatamodelLoaderBase datamodelLoader;
    private DatamodelBase datamodel;

	private ApplicationConfig appConfig;
	
	private IValueManager valueManager;
	
	private IActorManager actorManager;
	
	private IDatamodelService datamodelService;

    public DatamodelManager(IManagerRegistration managerRegistration) {
		super("DatamodelManager", managerRegistration);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_UNKNOWN;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
	}

	@Override
	public DatamodelBase getDatamodel() {
		return datamodel;
	}

	public void registerValues() {
		// register values
		for (String key : datamodel.getValues().keySet()) {
			log.debug("Register value {}", key);
			valueManager.registerValue(datamodel.getValues().get(key));
		}
	}

	public void registerActors() {
		// register actors
		for (String key : datamodel.getActors().keySet()) {
			log.debug("Register actor {}", key);
			actorManager.registerActor(datamodel.getActors().get(key));
			valueManager.registerValue(datamodel.getValues().get(key));
		}
	}

	@Override
	public void save() {
		datamodelLoader.save(datamodel);
	}

	@Override
	public void initComplete() {
		log.info("Init Datamodel");
		
	    String datamodelLoaderName = appConfig.getDatamodel().getLoader();

	    if (datamodelLoaderName.equals(HttpDatamodelLoader.LOADER_TYPE_NAME)) {
	        datamodelLoader = new HttpDatamodelLoader(appConfig.getDatamodel().getUrl());
	    //} else if (datamodelLoaderName.equals(FileDataModelLoader.LOADER_TYPE_NAME)) {
	        //datamodelLoader = new FileDataModelLoader(appConfig.getDatamodel().getFilePath());
	    } else if (datamodelLoaderName.equals(TestDatamodelLoader.LOADER_TYPE_NAME)) {
	        datamodelLoader = new TestDatamodelLoader();
	    } else if (datamodelLoaderName.equals(DBDatamodelLoader.LOADER_TYPE_NAME)) {
	    	datamodelLoader = new DBDatamodelLoader(datamodelService, appConfig.getDatamodel().getModelName());
	    } else {
	        log.warn("Unknown datamodel loader {}", datamodelLoaderName);
	    }
	    

	    /*
	    DBDatamodel model = new DBDatamodel("default");
	    ValueGroup vg = model.addValueGroup("testGroup");
	    model.addDigitalActor(vg, "act1", ValueType.VT_BRIGHTNESS, false, VALUE_TIMEOUT.VT_LONG);
	    model.addBooleanValue(vg, "test123", ValueType.VT_MOTION, VALUE_TIMEOUT.VT_NONE);
	    FileDataModelLoader testfd = new FileDataModelLoader("test.json");
	    testfd.save(model);
	    datamodelLoader.save(model);
	    */
	    
	    datamodel = datamodelLoader.load();

	    log.info("Datamodel loaded");

	    registerValues();

	    //registerActors();
	}

}
