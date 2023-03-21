package com.osh.service;

import com.osh.actor.ActorBase;
import com.osh.actor.ActorCmds;
import com.osh.actor.AudioPlaybackActor;
import com.osh.actor.DigitalActor;
import com.osh.manager.IMqttSupport;

import java.util.List;

public interface IActorService extends IMqttSupport {

	void registerActor(ActorBase actorBase);

    void publishCmd(ActorBase actor, ActorCmds actorCmd);

    void publishCmd(ActorBase actor, ActorCmds actorCmd, Object value);

    ActorBase getActor(String fullId);

    List<ActorBase> getActors(Class<? extends ActorBase> classFilter);
}
