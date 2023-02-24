package com.osh.actor;

import com.osh.SerializationSupport;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class ShutterActor extends ActorBase<ShutterActor, Integer> implements SerializationSupport {
    public ShutterActor(ValueGroup valueGroup, String id, ValueType valueType) {
        super(valueGroup, id, valueType);
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
}
