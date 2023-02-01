package com.osh.device;

import com.osh.SerializationSupport;

public class KnownDevice extends DeviceBase implements SerializationSupport {
	
	private String name;

	public KnownDevice(String id, String serviceId, String name) {
		super(id, serviceId);
		this.name = name;
	}

	public KnownDevice() {
		super();
	}

	public String getName() {
		return name;
	}

}
