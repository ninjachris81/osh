package com.osh.actor;

import android.util.Log;

import java.util.HashMap;
import java.util.Map;

import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;
import com.osh.value.ValueManager;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ActorManager extends ManagerBase implements IActorManager {

	private static final Logger log = LoggerFactory.getLogger(ActorManager.class);

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
		if (msg instanceof ActorMessage) {
			if (actors.containsKey(((ActorMessage) msg).getFullId())) {
				ActorBase actor = actors.get(((ActorMessage) msg).getFullId());
				actor.triggerCmd(((ActorMessage) msg).getCmd(), "Message received");
			}
		} else {
			log.warn("Invalid actor: " + ((ActorMessage) msg).getFullId());
		}
	}

	@Override
	public void initComplete() {

	}

}
