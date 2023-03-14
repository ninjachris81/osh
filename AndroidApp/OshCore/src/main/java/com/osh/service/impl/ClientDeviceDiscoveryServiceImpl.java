package com.osh.service.impl;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.service.IDeviceDiscoveryService;

public class ClientDeviceDiscoveryServiceImpl implements IDeviceDiscoveryService {

	public ClientDeviceDiscoveryServiceImpl() {
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_UNKNOWN;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
	}

	@Override
	public String getDeviceId() {
		return "AndroidTestClient";
	}

	// TODO: implement bc


}
