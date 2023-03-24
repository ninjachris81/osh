package com.osh.actor;

import com.osh.SerializationSupport;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class ShutterActor extends ActorBase<ShutterActor, Integer> implements SerializationSupport {

    public static final int SHUTTER_OPERATION_MODE_AUTO = 0;
    public static final int SHUTTER_OPERATION_MODE_MANUAL = 1;

    public static final int SHUTTER_STATE_OPENED = 0;
    public static final int SHUTTER_STATE_CLOSED = 100;
    private final boolean tiltSupport;
    private final long fullCloseDuration;
    private final long fullTiltDuration;

    public ShutterActor(ValueGroup valueGroup, String id, ValueType valueType, boolean tiltSupport, long fullCloseDuration, long fullTiltDuration) {
        super(valueGroup, id, valueType);
        this.tiltSupport = tiltSupport;
        this.fullCloseDuration = fullCloseDuration;
        this.fullTiltDuration = fullTiltDuration;
    }
    @Override
    public boolean cmdSupported(ActorCmds cmd) {
        switch(cmd) {
            case ACTOR_CMD_STOP:
            case ACTOR_CMD_UP:
            case ACTOR_CMD_DOWN:
            case ACTOR_CMD_SHUTTER_HALF_CLOSE:
            case ACTOR_CMD_SHUTTER_HALF_OPEN:
            case ACTOR_CMD_SHUTTER_FULL_OPEN:
            case ACTOR_CMD_SHUTTER_TURN_OPEN:
            case ACTOR_CMD_SHUTTER_TURN_CLOSE:
                return true;
            default:
                return false;
        }
    }

    @Override
    protected void _triggerCmd(ActorCmds cmd) {

    }

    @Override
    protected Integer _updateValue(Object newValue) {
        if (newValue instanceof Integer) {
            return (Integer) newValue;
        } else {
            return null;
        }
    }

    public boolean isTiltSupport() {
        return tiltSupport;
    }

    public long getFullCloseDuration() {
        return fullCloseDuration;
    }

    public long getFullTiltDuration() {
        return fullTiltDuration;
    }

    public String getStateAsString() {
        if (this.value == null) return "";
        if (this.value == SHUTTER_STATE_OPENED) return "Opened";
        if (this.value == SHUTTER_STATE_CLOSED) return "Closed";
        return this.value + " %";
    }
}
