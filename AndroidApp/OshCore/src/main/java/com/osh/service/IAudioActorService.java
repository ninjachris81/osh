package com.osh.service;

import com.osh.actor.AudioPlaybackActor;

import java.util.List;

public interface IAudioActorService {
    List<AudioPlaybackActor> getAudioActors();

    List<AudioPlaybackActor> getAudioActorsByRoom(String roomId);
}
