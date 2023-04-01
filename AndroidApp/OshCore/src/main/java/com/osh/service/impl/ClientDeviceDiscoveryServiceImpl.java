package com.osh.service.impl;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.service.ICommunicationService;
import com.osh.service.IDeviceDiscoveryService;

public class ClientDeviceDiscoveryServiceImpl implements IDeviceDiscoveryService {

	private final String clientId;

	public ClientDeviceDiscoveryServiceImpl(ICommunicationService communicationService, String clientId) {
		this.clientId = clientId;
		communicationService.registerMessageType(MESSAGE_TYPE.MESSAGE_TYPE_DEVICE_DISCOVERY, this);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_DEVICE_DISCOVERY;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
	}

	@Override
	public String getDeviceId() {
		return clientId;
	}

	// TODO: implement bc


}
