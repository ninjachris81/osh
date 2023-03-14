package com.osh.actor;

import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

public class ToggleActor extends ActorBase<ToggleActor, Boolean> {
    public ToggleActor(ValueGroup valueGroup, String id) {
        super(valueGroup, id, ValueType.VT_VIRTUAL_ACTOR);
    }

    @Override
    public boolean cmdSupported(ActorCmds cmd) {
        return cmd == ActorCmds.ACTOR_CMD_TOGGLE;
    }

    @Override
    protected void _triggerCmd(ActorCmds cmd) {

    }

    @Override
    protected Boolean _updateValue(Object newValue) {
        if (newValue instanceof Boolean) {
            return (Boolean) newValue;
        } else {
            return null;
        }
    }
}
