package com.osh.device;

import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;

public abstract class DeviceDiscoveryManagerBase extends ManagerBase {

	public DeviceDiscoveryManagerBase(String id, IManagerRegistration managerRegistration) {
		super(id, managerRegistration);
	}

}
