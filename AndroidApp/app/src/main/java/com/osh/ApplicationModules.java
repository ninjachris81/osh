package com.osh;

import com.osh.config.ApplicationConfig;
import com.osh.config.IApplicationConfig;

import javax.inject.Singleton;

import dagger.Module;
import dagger.Provides;
import dagger.hilt.InstallIn;
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
