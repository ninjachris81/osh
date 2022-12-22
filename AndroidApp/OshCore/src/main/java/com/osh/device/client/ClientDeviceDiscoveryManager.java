package com.osh.device.client;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.device.DeviceDiscoveryManagerBase;
import com.osh.manager.IManagerRegistration;

public class ClientDeviceDiscoveryManager extends DeviceDiscoveryManagerBase {

	public ClientDeviceDiscoveryManager(IManagerRegistration managerRegistration) {
		super("ClientDeviceDiscoveryManager", managerRegistration);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_UNKNOWN;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
	}

}
