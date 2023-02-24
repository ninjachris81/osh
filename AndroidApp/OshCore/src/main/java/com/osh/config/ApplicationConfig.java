package com.osh.config;

import com.osh.communication.mqtt.config.MqttConfig;
import com.osh.database.config.DatabaseConfig;
import com.osh.datamodel.config.DatamodelConfig;

public class ApplicationConfig implements IApplicationConfig {
	
	private final MqttConfig mqtt = new MqttConfig();
	
	private final DatamodelConfig datamodel = new DatamodelConfig();

	private final DatabaseConfig database = new DatabaseConfig();

	/*
	public void setMqtt(MqttConfig mqtt) {
		this.mqtt = mqtt;
	}
	*/

	@Override
	public MqttConfig getMqtt() {
		return mqtt;
	}

	@Override
	public DatamodelConfig getDatamodel() {
		return datamodel;
	}

	@Override
	public DatabaseConfig getDatabase() {
		return database;
	}

	/*
	public void setDatamodel(DatamodelConfig datamodel) {
		this.datamodel = datamodel;
	}
	*/
	
}
