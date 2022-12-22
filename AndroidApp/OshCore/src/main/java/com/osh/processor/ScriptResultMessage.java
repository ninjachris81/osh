package com.osh.processor;

import org.apache.commons.lang3.StringUtils;

import com.osh.communication.MessageBase;

public class ScriptResultMessage<T> extends MessageBase {

    private String processorTaskId;
    private T value;

	
	public ScriptResultMessage(String processorTaskId, T value) {
		this.processorTaskId = processorTaskId;
		this.value = value;
	}

	@Override
	public MESSAGE_TYPE getMessageType() {
		return MESSAGE_TYPE.MESSAGE_TYPE_SCRIPT_RESULT;
	}

	@Override
	public String getFirstLevelId() {
		return processorTaskId;
	}

	@Override
	public String getSecondLevelId() {
		return StringUtils.EMPTY;
	}

	public String getProcessorTaskId() {
		return processorTaskId;
	}

	public void setProcessorTaskId(String processorTaskId) {
		this.processorTaskId = processorTaskId;
	}

	public T getValue() {
		return value;
	}

	public void setValue(T value) {
		this.value = value;
	}
	
	

}
