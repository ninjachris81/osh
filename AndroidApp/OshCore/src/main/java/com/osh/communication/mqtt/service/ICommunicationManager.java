package com.osh.communication.mqtt.service;

import com.osh.communication.MessageBase;

public interface ICommunicationManager {
	
	public void sendMessage(MessageBase msg);

}
