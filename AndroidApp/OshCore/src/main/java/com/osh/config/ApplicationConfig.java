package com.osh.config;

import com.osh.communication.mqtt.config.MqttConfig;
import com.osh.datamodel.config.DatamodelConfig;

public class ApplicationConfig implements IApplicationConfig {
	
	private MqttConfig mqtt = new MqttConfig();
	
	private DatamodelConfig datamodel = new DatamodelConfig();

	public void setMqtt(MqttConfig mqtt) {
		this.mqtt = mqtt;
	}

	@Override
	public MqttConfig getMqtt() {
		return mqtt;
	}

	@Override
	public DatamodelConfig getDatamodel() {
		return datamodel;
	}

	public void setDatamodel(DatamodelConfig datamodel) {
		this.datamodel = datamodel;
	}
	
}
