package com.osh.actor;

import com.osh.value.ValueBase;

public enum ActorCmds {

    ACTOR_CMD_UNKNOWN(0),
    ACTOR_CMD_ON(1),
    ACTOR_CMD_OFF(2),
    ACTOR_CMD_UP(3),
    ACTOR_CMD_DOWN(4),
    ACTOR_CMD_START(5),
    ACTOR_CMD_STOP(6),
    ACTOR_CMD_PAUSE(7),
    ACTOR_CMD_TOGGLE(8),
    ACTOR_CMD_SHUTTER_HALF_CLOSE(40),
    ACTOR_CMD_SHUTTER_HALF_OPEN(41),
    ACTOR_CMD_SHUTTER_FULL_OPEN(42),
    ACTOR_CMD_SHUTTER_TURN_OPEN(43),
    ACTOR_CMD_SHUTTER_TURN_CLOSE(44),
    ;

    private final int value;

    ActorCmds(int value) {
        this.value = value;
    }

    public static ActorCmds of(int val) {
        for (ActorCmds cmd : ActorCmds.values()) {
            if (cmd.value == val) return cmd;
        }

        return null;

    }
}
