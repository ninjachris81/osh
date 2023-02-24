package com.osh.config;

import com.osh.communication.mqtt.config.MqttConfig;
import com.osh.database.config.DatabaseConfig;
import com.osh.datamodel.config.DatamodelConfig;

public interface IApplicationConfig {

    MqttConfig getMqtt();

    DatamodelConfig getDatamodel();

    DatabaseConfig getDatabase();
}
