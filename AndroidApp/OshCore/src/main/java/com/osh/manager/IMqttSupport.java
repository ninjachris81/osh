package com.osh.manager;

import com.osh.Identifyable;
import com.osh.communication.MessageBase;

public interface IMqttSupport {
	
	public MessageBase.MESSAGE_TYPE getMessageType();

	public void handleReceivedMessage(MessageBase msg);

}
