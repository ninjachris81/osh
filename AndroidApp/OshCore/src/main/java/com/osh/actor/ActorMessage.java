package com.osh.actor;

import static com.osh.value.ValueBase.VALUE_SEPARATOR;

import com.osh.communication.MessageBase;

public class ActorMessage extends MessageBase {
	
	private String actorGroupId;
	private String actorId;
	private ActorCmds cmd;
	
	public ActorMessage(String actorGroupId, String actorId, ActorCmds cmd) {
		super();
		this.actorGroupId = actorGroupId;
		this.actorId = actorId;
		this.cmd = cmd;
	}

	public ActorMessage(ActorBase actor, ActorCmds actorCmd) {
		this(actor.getValueGroup().getId(), actor.getId(), actorCmd);
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_ACTOR;
	}

	@Override
	public String getFirstLevelId() {
		return actorGroupId;
	}

	@Override
	public String getSecondLevelId() {
		return actorId;
	}

	public String getActorGroupId() {
		return actorGroupId;
	}

	public String getActorId() {
		return actorId;
	}

	public ActorCmds getCmd() {
		return cmd;
	}

	public String getFullId() {
		return actorGroupId + VALUE_SEPARATOR + actorId;
	}

}
