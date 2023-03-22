package com.osh.service;

import com.osh.datamodel.meta.AudioPlaybackSource;

import java.util.List;

public interface IAudioSourceService {

    List<AudioPlaybackSource> getAudioPlaybackSources();
}
