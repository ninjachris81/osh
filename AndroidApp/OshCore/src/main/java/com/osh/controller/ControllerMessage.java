package com.osh.controller;

import java.util.Map;

import org.apache.commons.lang3.StringUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import com.osh.communication.MessageBase;

public class ControllerMessage<T> extends MessageBase {
	
	private static final Logger log = LoggerFactory.getLogger(ControllerMessage.class);

	public static final String CONTROLLER_TYPE_ATTR = "type";

	enum CONTROLLER_CMD_TYPE {
        CCT_UNKNOWN,
        CCT_ENABLE
    };
	
	private String controllerId;
	private T data;
	private CONTROLLER_CMD_TYPE cmdType;
	
	public ControllerMessage(String controllerId, Map<String, Object> data) {
	    if (data.containsKey(CONTROLLER_TYPE_ATTR)) {
	        cmdType = (CONTROLLER_CMD_TYPE) data.get(CONTROLLER_TYPE_ATTR);
	    } else {
	    	log.warn("Invalid controller data: {}", data);
	    }
	}

	public ControllerMessage(String controllerId, T data) {
		this.controllerId = controllerId;
		this.data = data;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_CONTROLLER;
	}

	@Override
	public String getFirstLevelId() {
		return controllerId;
	}

	@Override
	public String getSecondLevelId() {
		return StringUtils.EMPTY;
	}

	public String getControllerId() {
		return controllerId;
	}

	public void setControllerId(String controllerId) {
		this.controllerId = controllerId;
	}

	public T getData() {
		return data;
	}

	public void setData(T data) {
		this.data = data;
	}

	public CONTROLLER_CMD_TYPE getCmdType() {
		return cmdType;
	}

	public void setCmdType(CONTROLLER_CMD_TYPE cmdType) {
		this.cmdType = cmdType;
	}
	
}
