package com.osh.communication.mqtt.service;

import com.osh.communication.MessageBase;
import com.osh.utils.IObservableBoolean;

public interface ICommunicationManager {
	
	public void sendMessage(MessageBase msg);

	public IObservableBoolean connectedState();

}
