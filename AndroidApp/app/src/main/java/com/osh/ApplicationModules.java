package com.osh;

import com.osh.actor.ActorManager;
import com.osh.actor.IActorManager;
import com.osh.communication.mqtt.service.ICommunicationManager;
import com.osh.communication.mqtt.service.impl.MqttCommunicationManager;
import com.osh.config.ApplicationConfig;
import com.osh.config.IApplicationConfig;
import com.osh.doorunlock.DoorUnlockManager;
import com.osh.doorunlock.IDoorUnlockManager;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerRegistration;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import dagger.hilt.InstallIn;
import dagger.hilt.android.components.ActivityComponent;
import dagger.hilt.android.scopes.ActivityScoped;
import dagger.hilt.components.SingletonComponent;

@Module
@InstallIn(SingletonComponent.class)
public class ApplicationModules {

    @Provides
    @Singleton
    static IApplicationConfig provideApplicationConfig() {
        return new ApplicationConfig();
    }

}