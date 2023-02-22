package com.osh;

import com.osh.actor.ActorManager;
import com.osh.actor.IActorManager;
import com.osh.communication.mqtt.service.ICommunicationManager;
import com.osh.communication.mqtt.service.impl.MqttCommunicationManager;
import com.osh.config.IApplicationConfig;
import com.osh.doorunlock.DoorUnlockManager;
import com.osh.doorunlock.IDoorUnlockManager;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerRegistration;
import com.osh.value.IValueManager;
import com.osh.value.ValueManager;
import com.osh.wbb12.IWBB12Manager;
import com.osh.wbb12.WBB12Manager;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import dagger.hilt.InstallIn;
import dagger.hilt.components.SingletonComponent;

@Module
@InstallIn(SingletonComponent.class)
public class ManagerModules {

    @Provides
    @Singleton
    static IManagerRegistration provideManagerRegistration() {
        return new ManagerRegistration(ManagerRegistration.INSTANCE_ROLE.GUI, 5);
    }

    @Provides
    @Singleton
    static IActorManager provideActorManager(IManagerRegistration managerRegistration) {
        return new ActorManager(managerRegistration);
    }

    @Provides
    @Singleton
    static IValueManager provideValueManager(IManagerRegistration managerRegistration) {
        return new ValueManager(managerRegistration);
    }

    @Provides
    @Singleton
    static ICommunicationManager provideCommunicationManager(IApplicationConfig applicationConfig, IManagerRegistration managerRegistration) {
        return new MqttCommunicationManager(applicationConfig, managerRegistration);
    }

    @Provides
    @Singleton
    static IDoorUnlockManager provideDoorUnlockManager(IManagerRegistration managerRegistration, ICommunicationManager communicationManager) {
        return new DoorUnlockManager(managerRegistration,communicationManager);
    }

    @Provides
    @Singleton
    static IWBB12Manager provideWBB12Manager(IManagerRegistration managerRegistration, IValueManager valueManager) {
        return new WBB12Manager(managerRegistration, valueManager);
    }

}
