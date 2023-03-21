package com.osh.service.impl;

import com.osh.doorunlock.IDoorUnlockManager;
import com.osh.service.IActorService;
import com.osh.service.IAudioActorService;
import com.osh.service.ICommunicationService;
import com.osh.service.IDatabaseService;
import com.osh.service.IDatamodelService;
import com.osh.service.IServiceContext;
import com.osh.service.IValueService;

public class ServiceContextImpl implements IServiceContext {
    private final IActorService actorService;
    private final IAudioActorService audioActorService;
    private final IDoorUnlockManager doorUnlockManager;
    private final IValueService valueService;
    private final IDatabaseService databaseService;
    private final IDatamodelService datamodelService;
    private final ICommunicationService communicationService;

    public ServiceContextImpl(IActorService actorService, IAudioActorService audioActorService, IDoorUnlockManager doorUnlockManager, IValueService valueService, IDatabaseService databaseService, IDatamodelService datamodelService, ICommunicationService communicationService) {
        this.actorService = actorService;
        this.audioActorService = audioActorService;
        this.doorUnlockManager = doorUnlockManager;
        this.valueService = valueService;
        this.databaseService = databaseService;
        this.datamodelService = datamodelService;
        this.communicationService = communicationService;
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
    public IDoorUnlockManager getDoorUnlockManager() {
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
}
