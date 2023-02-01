package com.osh.warn;

import com.osh.communication.MessageBase;

public class SystemWarningMessage extends MessageBase {
	
	private String deviceId;
	private String msg;

	public SystemWarningMessage(String deviceId, String msg) {
		this.deviceId = deviceId;
		this.msg = msg;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_SYSTEM_WARNING;
	}

	@Override
	public String getFirstLevelId() {
		return deviceId;
	}

	@Override
	public String getSecondLevelId() {
		return "";
	}

	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	public String getMsg() {
		return msg;
	}

	public void setMsg(String msg) {
		this.msg = msg;
	}
	
}
