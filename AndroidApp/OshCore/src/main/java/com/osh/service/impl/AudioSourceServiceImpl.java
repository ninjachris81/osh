package com.osh.service.impl;

import com.osh.datamodel.meta.AudioPlaybackSource;
import com.osh.service.IAudioSourceService;
import com.osh.service.IDatamodelService;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;

public class AudioSourceServiceImpl implements IAudioSourceService {


    private final IDatamodelService datamodelService;

    public AudioSourceServiceImpl(IDatamodelService datamodelService) {
        this.datamodelService = datamodelService;
    }

    @Override
    public List<AudioPlaybackSource> getAudioPlaybackSources() {
        List<AudioPlaybackSource> returnList = new ArrayList<>(datamodelService.getDatamodel().getAudioPlaybackSources().values());
        returnList.sort(Comparator.comparing(AudioPlaybackSource::getName));
        return returnList;
    }
}
