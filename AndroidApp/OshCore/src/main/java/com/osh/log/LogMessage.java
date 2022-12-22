package com.osh.log;

import org.apache.commons.lang3.StringUtils;

import com.osh.communication.MessageBase;

public class LogMessage extends MessageBase {
	
	public enum MsgType {
		LOG_DEBUG,
		LOG_INFO,
		LOG_WARN,
		LOG_CRITICAL,
		LOG_FATAL;
		
		public String toString() {
			switch(this) {
			case LOG_DEBUG: return "debug";
			case LOG_INFO: return "info";
			case LOG_WARN: return "warn";
			case LOG_CRITICAL: return "critical";
			case LOG_FATAL: return "fatal";
			default: return StringUtils.EMPTY;
			}
		}
		
		public static MsgType fromString(String type) {
			if (type.equals("debug")) return LOG_DEBUG;
			if (type.equals("info")) return LOG_INFO;
			if (type.equals("warn")) return LOG_WARN;
			if (type.equals("critical")) return LOG_CRITICAL;
			if (type.equals("fatal")) return LOG_FATAL;
			return null;
		}
	}
	
    private String deviceId;
    private MsgType logType;
    private String message;


	public LogMessage(String deviceId, MsgType logType, String message) {
		this.deviceId = deviceId;
		this.logType = logType;
		this.message = message;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_LOG;
	}

	@Override
	public String getFirstLevelId() {
		return deviceId;
	}

	@Override
	public String getSecondLevelId() {
		return logType.toString();
	}

	public String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(String deviceId) {
		this.deviceId = deviceId;
	}

	public MsgType getLogType() {
		return logType;
	}

	public void setLogType(MsgType logType) {
		this.logType = logType;
	}

	public String getMessage() {
		return message;
	}

	public void setMessage(String message) {
		this.message = message;
	}
	
	

}
