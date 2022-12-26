package com.osh.manager;

import com.osh.Identifyable;
import com.osh.communication.MessageBase;

public abstract class ManagerBase extends Identifyable {
	
	protected final IManagerRegistration managerRegistration;
	
	public abstract MessageBase.MESSAGE_TYPE getMessageType();
	
	public ManagerBase(String id, IManagerRegistration managerRegistration) {
		super(id);
		this.managerRegistration = managerRegistration;
		this.managerRegistration.registerManager(this);
	}

	public IManagerRegistration getManagerRegistration() {
		return managerRegistration;
	}

	public abstract void handleReceivedMessage(MessageBase msg);

	public abstract void initComplete();
}
