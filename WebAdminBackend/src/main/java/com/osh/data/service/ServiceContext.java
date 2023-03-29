package com.osh.data.service;

import com.osh.data.entity.KnownDevice;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ServiceContext {


    @Autowired
    private AudioPlaybackSourceService audioPlaybackSourceService;

    @Autowired
    private KnownAreaService knownAreaService;

    @Autowired
    private KnownDeviceService knownDeviceService;

    @Autowired
    private KnownRoomService knownRoomService;

    @Autowired
    private ProcessorTaskService processorTaskService;

    @Autowired
    private ProcessorVariableService processorVariableService;

    @Autowired
    private ValueGroupService valueGroupService;

    public AudioPlaybackSourceService getAudioPlaybackSourceService() {
        return audioPlaybackSourceService;
    }

    public KnownAreaService getKnownAreaService() {
        return knownAreaService;
    }

    public KnownDeviceService getKnownDeviceService() {
        return knownDeviceService;
    }

    public KnownRoomService getKnownRoomService() {
        return knownRoomService;
    }

    public ProcessorTaskService getProcessorTaskService() {
        return processorTaskService;
    }

    public ProcessorVariableService getProcessorVariableService() {
        return processorVariableService;
    }

    public ValueGroupService getValueGroupService() {
        return valueGroupService;
    }
}
