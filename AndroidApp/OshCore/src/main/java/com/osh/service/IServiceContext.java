package com.osh.service;

import com.osh.doorunlock.IDoorUnlockManager;

import javax.inject.Inject;

public interface IServiceContext {

    IActorService getActorService();

    IAudioActorService getAudioActorService();

    IDoorUnlockManager getDoorUnlockManager();

    IValueService getValueService();

    IDatabaseService getDatabaseService();

    IDatamodelService getDatamodelService();

    ICommunicationService getCommunicationService();

}
