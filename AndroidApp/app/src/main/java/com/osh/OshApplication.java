package com.osh;

import static androidx.preference.PreferenceManager.getDefaultSharedPreferences;

import android.app.Application;
import android.content.SharedPreferences;

import com.osh.config.IApplicationConfig;

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

        String clientId = prefs.getString(getString(R.string.mqtt_client_id_key), "");
        if (clientId.isEmpty()) {
            // set new random client ID
            clientId = "AndroidClient_" + System.currentTimeMillis();
            prefs.edit().putString(getString(R.string.mqtt_client_id_key), clientId).commit();
        }
        applicationConfig.getMqtt().setClientId(clientId);

        applicationConfig.getMqtt().setServerHost(prefs.getString(getString(R.string.mqtt_host_key), "127.0.0.1"));
        applicationConfig.getMqtt().setServerPort(Integer.parseInt(prefs.getString(getString(R.string.mqtt_port_key), "1883")));
        applicationConfig.getDatabase().setHost(prefs.getString(getString(R.string.db_host), "192.168.177.1"));
        applicationConfig.getDatabase().setPort(Integer.parseInt(prefs.getString(getString(R.string.db_port), "5432")));
        applicationConfig.getDatabase().setName(prefs.getString(getString(R.string.db_name), "osh"));
        applicationConfig.getDatabase().setUsername(prefs.getString(getString(R.string.db_username), "osh"));
        applicationConfig.getDatabase().setPassword(prefs.getString(getString(R.string.db_password), "osh"));
    }
}
