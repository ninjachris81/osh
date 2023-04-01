package com.osh.actor;

import com.osh.SerializationSupport;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class DoorActor extends ActorBase<DoorActor, Boolean> implements SerializationSupport {

    public DoorActor(ValueGroup valueGroup, String id, ValueType valueType) {
        super(valueGroup, id, valueType);
    }
    @Override
    public boolean cmdSupported(ActorCmds cmd) {
        return false;
    }

    @Override
    protected void _triggerCmd(ActorCmds cmd) {

    }

    @Override
    protected Boolean _updateValue(Object newValue) {
        return null;
    }
}
