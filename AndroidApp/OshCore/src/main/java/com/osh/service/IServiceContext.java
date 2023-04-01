package com.osh.service;

public interface IServiceContext {

    IActorService getActorService();

    IAudioActorService getAudioActorService();

    IAudioSourceService getAudioSourceService();

    IDoorUnlockService getDoorUnlockManager();

    IValueService getValueService();

    IDatabaseService getDatabaseService();

    IDatamodelService getDatamodelService();

    ICommunicationService getCommunicationService();

    IDeviceDiscoveryService getDeviceDiscoveryService();

}
