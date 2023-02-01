package com.osh.device;

import com.osh.communication.MessageBase;

public class DeviceDiscoveryMessage extends MessageBase {
	
    private String deviceId;
    private String serviceId;

	public DeviceDiscoveryMessage(String deviceId, String serviceId) {
		this.deviceId = deviceId;
		this.serviceId = serviceId;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_DEVICE_DISCOVERY;
	}

	@Override
	public String getFirstLevelId() {
		return deviceId;
	}

	@Override
	public String getSecondLevelId() {
		return serviceId;
	}

	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	public String getServiceId() {
		return serviceId;
	}

	public void setServiceId(String serviceId) {
		this.serviceId = serviceId;
	}
	
}
