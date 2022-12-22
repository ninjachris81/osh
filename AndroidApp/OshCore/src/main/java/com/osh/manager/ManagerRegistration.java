package com.osh.manager;

import java.util.HashMap;
import java.util.Map;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ManagerRegistration implements IManagerRegistration {
	
	private static final Logger log = LoggerFactory.getLogger(ManagerRegistration.class);

    public enum INSTANCE_ROLE {
        UNKNOWN,
        SERVER,
        CLIENT,
        GUI
    };
    
    protected INSTANCE_ROLE instanceRole;
    
    protected Map<String, ManagerBase> managers = new HashMap<>();

    @Override
	public INSTANCE_ROLE getInstanceRole() {
		return instanceRole;
	}
	
	public ManagerRegistration(INSTANCE_ROLE instanceRole) {
		super();
		this.instanceRole = instanceRole;
	}

	@Override
	public void registerManager(ManagerBase manager) {
		log.debug("Register manager {}", manager.getId());
	    managers.put(manager.getId(), manager);
	}

	public Map<String, ManagerBase> getManagers() {
		return managers;
	}
    
}
