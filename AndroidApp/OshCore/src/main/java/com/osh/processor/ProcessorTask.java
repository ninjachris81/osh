package com.osh.processor;

import com.osh.SerializableIdentifyable;
import com.osh.SerializationSupport;

public class ProcessorTask extends SerializableIdentifyable implements SerializationSupport {
	
    public enum ProcessorTaskType {
        PTT_INTERVAL,
        PTT_ONLY_ONCE,
        PTT_TRIGGER
    };
    
    private String scriptCode;
    private String runCondition;
    private long scheduleInterval;
    
    private ProcessorTaskType processorTaskType = ProcessorTaskType.PTT_INTERVAL;
    
	public ProcessorTask(String id, ProcessorTaskType taskType, String scriptCode, String runCondition,
			long scheduleInterval) {
		super(id);
		this.processorTaskType = taskType;
		this.scriptCode = scriptCode;
		this.runCondition = runCondition;
		this.scheduleInterval = scheduleInterval;
	}

	public ProcessorTask() {
	}

	
}
