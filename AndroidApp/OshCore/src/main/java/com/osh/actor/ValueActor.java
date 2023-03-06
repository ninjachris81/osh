package com.osh.actor;

import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class ValueActor extends ActorBase {

    @Override
    protected Object _updateValue(Object newValue) {
        return newValue;
    }

    public ValueActor(ValueGroup valueGroup, String id, ValueType valueType) {
        super(valueGroup, id, valueType);
    }

    @Override
    public boolean cmdSupported(ActorCmds cmd) {
        return cmd == ActorCmds.ACTOR_CMD_SET_VALUE;
    }

    @Override
    protected void _triggerCmd(ActorCmds cmd) {

    }



}
