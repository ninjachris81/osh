package com.osh.communication;

public abstract class MessageBase {

    public enum MESSAGE_TYPE {
        MESSAGE_TYPE_UNKNOWN,
        MESSAGE_TYPE_VALUE,
        MESSAGE_TYPE_ACTOR,
        MESSAGE_TYPE_ACTOR_CONFIG,
        MESSAGE_TYPE_DEVICE_DISCOVERY,
        MESSAGE_TYPE_SYSTEM_TIME,
        MESSAGE_TYPE_SYSTEM_WARNING,
        MESSAGE_TYPE_CONTROLLER,
        MESSAGE_TYPE_LOG,
        MESSAGE_TYPE_SCRIPT_RESULT,
        MESSAGE_TYPE_DOOR_UNLOCK
    };
    
    public abstract MESSAGE_TYPE getMessageType();
    public abstract String getFirstLevelId();
    public abstract String getSecondLevelId();

}
