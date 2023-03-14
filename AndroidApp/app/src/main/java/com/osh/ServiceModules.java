package com.osh;

import com.osh.service.IActorService;
import com.osh.service.ICommunicationService;
import com.osh.service.IDatabaseService;
import com.osh.service.IDatamodelService;
import com.osh.service.IDeviceDiscoveryService;
import com.osh.service.impl.ActorServiceImpl;
import com.osh.service.impl.ClientDeviceDiscoveryServiceImpl;
import com.osh.service.impl.DatabaseServiceImpl;
import com.osh.service.impl.DatamodelServiceImpl;
import com.osh.service.impl.MqttCommunicationServiceImpl;
import com.osh.config.IApplicationConfig;
import com.osh.doorunlock.DoorUnlockManager;
import com.osh.doorunlock.IDoorUnlockManager;
import com.osh.service.IValueService;
import com.osh.service.impl.ValueServiceImpl;
import com.osh.wbb12.service.IWBB12Service;
import com.osh.wbb12.service.impl.WBB12ServiceImpl;

import java.sql.SQLException;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import dagger.hilt.InstallIn;
import dagger.hilt.components.SingletonComponent;

@Module
@InstallIn(SingletonComponent.class)
public class ServiceModules {

    @Provides
    @Singleton
    static IDatabaseService provideDatabaseService(IApplicationConfig applicationConfig) {
        try {
            return new DatabaseServiceImpl(applicationConfig);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Provides
    @Singleton
    static IDatamodelService provideDatamodelService(ICommunicationService communicationService, IDatabaseService databaseService, IValueService valueService, IActorService actorService) {
        try {
            return new DatamodelServiceImpl(communicationService, databaseService, valueService, actorService);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Provides
    @Singleton
    static IActorService provideActorManager(ICommunicationService communicationService, IValueService valueService) {
        return new ActorServiceImpl(communicationService, valueService);
    }

    @Provides
    @Singleton
    static IValueService provideValueManager(ICommunicationService communicationManager) {
        return new ValueServiceImpl(communicationManager);
    }

    @Provides
    @Singleton
    static ICommunicationService provideCommunicationManager(IApplicationConfig applicationConfig, IDeviceDiscoveryService deviceDiscoveryService) {
        return new MqttCommunicationServiceImpl(applicationConfig, deviceDiscoveryService);
    }

    @Provides
    @Singleton
    static IDoorUnlockManager provideDoorUnlockManager(ICommunicationService communicationManager) {
        return new DoorUnlockManager(communicationManager);
    }

    @Provides
    @Singleton
    static IWBB12Service provideWBB12Manager(IDatamodelService datamodelService, IValueService valueManager, IActorService actorService) {
        return new WBB12ServiceImpl(datamodelService, valueManager, actorService);
    }

    @Provides
    @Singleton
    static IDeviceDiscoveryService provideDeviceDiscoveryService() {
        return new ClientDeviceDiscoveryServiceImpl();
    }

}
