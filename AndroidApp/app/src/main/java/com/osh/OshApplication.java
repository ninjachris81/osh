package com.osh;

import static androidx.preference.PreferenceManager.getDefaultSharedPreferences;

import android.app.Application;
import android.content.SharedPreferences;

import com.osh.actor.IActorManager;
import com.osh.communication.mqtt.service.ICommunicationManager;
import com.osh.config.IApplicationConfig;
import com.osh.doorunlock.IDoorUnlockManager;

import javax.inject.Inject;

import dagger.hilt.android.HiltAndroidApp;

@HiltAndroidApp
public class OshApplication extends Application {

    @Inject
    IApplicationConfig applicationConfig;

    @Override
    public void onCreate() {
        super.onCreate();

        loadApplicationConfig();
    }

    private void loadApplicationConfig() {
        SharedPreferences prefs = getDefaultSharedPreferences(this);
        applicationConfig.getMqtt().setServerHost(prefs.getString(getString(R.string.mqtt_host_key), "127.0.0.1"));
        applicationConfig.getMqtt().setServerPort(Integer.parseInt(prefs.getString(getString(R.string.mqtt_port_key), "1883")));
        applicationConfig.getMqtt().setClientId("test_" + System.currentTimeMillis());
    }
}
