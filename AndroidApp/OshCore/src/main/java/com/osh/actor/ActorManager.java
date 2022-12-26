package com.osh.actor;

import java.util.HashMap;
import java.util.Map;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;

public class ActorManager extends ManagerBase implements IActorManager {

    protected Map<String, ActorBase> actors = new HashMap<>();

	public ActorManager(IManagerRegistration managerRegistration) {
		super("ActorManager", managerRegistration);
	}

	@Override
	public void registerActor(ActorBase actor) {
		actors.put(actor.getId(), actor);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_ACTOR;
	}

	@Override
	public void handleReceivedMessage(MessageBase msg) {
	}

	@Override
	public void initComplete() {

	}

}
