package com.osh.communication.mqtt;

import com.osh.communication.MessageBase;

public class MessageTypeInfo {
	
    public MessageBase.MESSAGE_TYPE messageType;
    public boolean isRetained;
    public String mqttTypePath;
    public int mqttPathLevels;

    public boolean dropOwnMessages;
}
