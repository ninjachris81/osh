package com.osh.actor;

import static com.osh.value.ValueBase.VALUE_SEPARATOR;

import com.osh.communication.MessageBase;
import com.osh.value.ValueMessage;

public class ActorMessage extends ValueMessage {
	private ActorCmds cmd;
	
	public ActorMessage(String actorGroupId, String actorId, Object value, ActorCmds cmd) {
		super(actorGroupId, actorId, value);
		this.cmd = cmd;
	}

	public ActorMessage(ActorBase actor, Object value, ActorCmds actorCmd) {
		this(actor.getValueGroup().getId(), actor.getId(), value, actorCmd);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_ACTOR;
	}


	public ActorCmds getCmd() {
		return cmd;
	}

}
