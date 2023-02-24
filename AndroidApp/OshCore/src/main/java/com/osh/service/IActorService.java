package com.osh.service;

import com.osh.actor.ActorBase;
import com.osh.actor.ActorCmds;
import com.osh.actor.DigitalActor;
import com.osh.manager.IMqttSupport;

public interface IActorService extends IMqttSupport {

	void registerActor(ActorBase actorBase);

    void publishCmd(ActorBase actor, ActorCmds actorCmd);
}
