package com.osh.device;

import com.osh.SerializableIdentifyable;

public class DeviceBase extends SerializableIdentifyable {
	
	public static final String DEVICE_FULLID_SEP = ".";

	protected String serviceId;
	
	protected boolean isOnline = false;
	
	protected long lastPing = 0;
	
	public DeviceBase(String id, String serviceId) {
		super(id);
		this.serviceId = serviceId;
	}

	public DeviceBase() {
		super();
	}

	public String getFullId() {
	    return id + DEVICE_FULLID_SEP + serviceId;
	}

	public String getServiceId() {
		return serviceId;
	}

	public void setServiceId(String serviceId) {
		this.serviceId = serviceId;
	}

}
