package com.osh.manager;

import java.util.Map;

import com.osh.manager.ManagerRegistration.INSTANCE_ROLE;

public interface IManagerRegistration {
	
	void registerManager(ManagerBase manager);

	Map<String, ManagerBase> getManagers();

	INSTANCE_ROLE getInstanceRole();
	
}
