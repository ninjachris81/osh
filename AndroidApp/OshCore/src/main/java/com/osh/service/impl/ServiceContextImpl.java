package com.osh.service.impl;

import com.osh.service.IDeviceDiscoveryService;
import com.osh.service.IDoorUnlockService;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.IAudioSourceService;
import com.osh.service.ICommunicationService;
import com.osh.service.IDatabaseService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

public class ServiceContextImpl implements IServiceContext {
    private final IActorService actorService;
    private final IAudioActorService audioActorService;
    private final IAudioSourceService audioSourceService;
    private final IDoorUnlockService doorUnlockManager;
    private final IValueService valueService;
    private final IDatabaseService databaseService;
    private final IDatamodelService datamodelService;
    private final ICommunicationService communicationService;

    private final IDeviceDiscoveryService deviceDiscoveryService;

    public ServiceContextImpl(IActorService actorService, IAudioActorService audioActorService, IAudioSourceService audioSourceService, IDoorUnlockService doorUnlockManager, IValueService valueService, IDatabaseService databaseService, IDatamodelService datamodelService, ICommunicationService communicationService, IDeviceDiscoveryService deviceDiscoveryService) {
        this.actorService = actorService;
        this.audioActorService = audioActorService;
        this.audioSourceService = audioSourceService;
        this.doorUnlockManager = doorUnlockManager;
        this.valueService = valueService;
        this.databaseService = databaseService;
        this.datamodelService = datamodelService;
        this.communicationService = communicationService;
        this.deviceDiscoveryService = deviceDiscoveryService;
    }

    @Override
    public IActorService getActorService() {
        return this.actorService;
    }

    @Override
    public IAudioActorService getAudioActorService() {
        return this.audioActorService;
    }

    @Override
    public IAudioSourceService getAudioSourceService() {
        return audioSourceService;
    }

    @Override
    public IDoorUnlockService getDoorUnlockManager() {
        return this.doorUnlockManager;
    }

    @Override
    public IValueService getValueService() {
        return this.valueService;
    }

    @Override
    public IDatabaseService getDatabaseService() {
        return this.databaseService;
    }

    @Override
    public IDatamodelService getDatamodelService() {
        return this.datamodelService;
    }

    @Override
    public ICommunicationService getCommunicationService() {
        return this.communicationService;
    }

    @Override
    public IDeviceDiscoveryService getDeviceDiscoveryService() {
        return this.deviceDiscoveryService;
    }
}
