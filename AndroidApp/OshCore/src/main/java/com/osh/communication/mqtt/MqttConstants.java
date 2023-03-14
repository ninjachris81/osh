package com.osh.communication.mqtt;

public class MqttConstants {
	
	public static final char MQTT_INVALID_PAYLOAD = ' ';
	
	public static final String MQTT_BASE_PATH = "osh";
	public static final String MQTT_PATH_SEP = "/";
	public static final String MQTT_WILDCARD = "#";
	
	public static final String MQTT_MESSAGE_TYPE_VA = "va";        // value
	public static final String MQTT_MESSAGE_TYPE_AC = "ac";        // actor
	public static final String MQTT_MESSAGE_TYPE_ACCO = "acco";   // actor config
	public static final String MQTT_MESSAGE_TYPE_DD = "dd";        // device discovery
	public static final String MQTT_MESSAGE_TYPE_ST = "st";        // system time
	public static final String MQTT_MESSAGE_TYPE_SW = "sw";        // system warnings
	public static final String MQTT_MESSAGE_TYPE_CO = "co";        // controller
	public static final String MQTT_MESSAGE_TYPE_LO = "lo";        // log
	public static final String MQTT_MESSAGE_TYPE_SR = "sr";        // script result reports
	public static final String MQTT_MESSAGE_TYPE_DU = "du";        // door unlock

	public static final String MQTT_SINGLE_VALUE_ATTR = "v";
	public static final String MQTT_ACTOR_CMD_ATTR = "c";
	public static final String MQTT_SENDER_DEVICE_ID_ATTR = "s";
	public static final String MQTT_TS = "t";


}
