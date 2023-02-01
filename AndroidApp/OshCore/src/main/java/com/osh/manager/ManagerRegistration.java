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

	protected int expectedCount;

    @Override
	public INSTANCE_ROLE getInstanceRole() {
		return instanceRole;
	}
	
	public ManagerRegistration(INSTANCE_ROLE instanceRole, int expectedCount) {
		super();
		this.instanceRole = instanceRole;
		this.expectedCount = expectedCount;
	}

	@Override
	public void registerManager(ManagerBase manager) {
		log.debug("Register manager {}", manager.getId());
	    managers.put(manager.getId(), manager);

		if (expectedCount == managers.size()) {
			log.info("All managers complete - init");

			for (ManagerBase m : managers.values()) {
				m.initComplete();
			}
		}
	}

	public Map<String, ManagerBase> getManagers() {
		return managers;
	}
    
}
