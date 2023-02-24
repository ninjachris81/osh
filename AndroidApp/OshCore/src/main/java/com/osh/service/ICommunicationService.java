package com.osh.service;

import com.osh.communication.MessageBase;
import com.osh.config.IApplicationConfig;
import com.osh.manager.IMqttSupport;
import com.osh.utils.IObservableBoolean;

public interface ICommunicationService {

    void connectMqtt();

    void registerMessageType(MessageBase.MESSAGE_TYPE messageType, IMqttSupport service);

    public void sendMessage(MessageBase msg);

	public IObservableBoolean connectedState();

}
