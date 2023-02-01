package com.osh.actor;

import java.util.Map;

import com.osh.communication.MessageBase;

public class ActorConfigMessage extends MessageBase {
	
	private String actorGroupId;
	private String actorId;
	private Map<String, Object> values;
	
	public ActorConfigMessage(String actorGroupId, String actorId, Map<String, Object> values) {
		super();
		this.actorGroupId = actorGroupId;
		this.actorId = actorId;
		this.values = values;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_ACTOR_CONFIG;
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

	public Map<String, Object> getValues() {
		return values;
	}
	
}
