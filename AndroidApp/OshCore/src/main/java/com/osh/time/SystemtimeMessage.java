package com.osh.time;

import org.apache.commons.lang3.StringUtils;

import com.osh.communication.MessageBase;

public class SystemtimeMessage extends MessageBase {
	
	private long ts;

	public SystemtimeMessage(long ts) {
		this.ts = ts;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_SYSTEM_TIME;
	}

	@Override
	public String getFirstLevelId() {
		return StringUtils.EMPTY;
	}

	@Override
	public String getSecondLevelId() {
		return StringUtils.EMPTY;
	}

	public long getTs() {
		return ts;
	}

	public void setTs(long ts) {
		this.ts = ts;
	}
	
}
