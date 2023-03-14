package com.osh.service.impl;

import java.util.HashMap;
import java.util.Map;

import com.osh.actor.ActorBase;
import com.osh.actor.ActorCmds;
import com.osh.actor.ActorMessage;
import com.osh.communication.MessageBase;
import com.osh.communication.MessageBase.MESSAGE_TYPE;
import com.osh.service.IActorService;
import com.osh.service.ICommunicationService;
import com.osh.service.IValueService;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class ActorServiceImpl implements IActorService {

	private static final Logger log = LoggerFactory.getLogger(ActorServiceImpl.class);

    protected Map<String, ActorBase> actors = new HashMap<>();

	private final ICommunicationService communicationService;

	private final IValueService valueService;

	public ActorServiceImpl(ICommunicationService communicationService, IValueService valueService) {
		this.communicationService = communicationService;
		this.valueService = valueService;
		communicationService.registerMessageType(getMessageType(), this);
	}

	@Override
	public void registerActor(ActorBase actor) {
		actors.put(actor.getFullId(), actor);
		valueService.registerValue(actor);
	}

	@Override
	public void publishCmd(ActorBase actor, ActorCmds actorCmd) {
		ActorMessage msg = new ActorMessage(actor, null, actorCmd);
		communicationService.sendMessage(msg);
	}

	@Override
	public void publishCmd(ActorBase actor, ActorCmds actorCmd, Object value) {
		ActorMessage msg = new ActorMessage(actor, value, actorCmd);
		communicationService.sendMessage(msg);
	}

	@Override
	public ActorBase getActor(String fullId) {
		return actors.get(fullId);
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

}
