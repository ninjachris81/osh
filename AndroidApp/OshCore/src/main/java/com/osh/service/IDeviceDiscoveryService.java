package com.osh.service;

import com.osh.communication.MessageBase;
import com.osh.manager.IMqttSupport;

public interface IDeviceDiscoveryService extends IMqttSupport {

    String getDeviceId();
}
