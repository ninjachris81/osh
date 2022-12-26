package com.osh.doorunlock;

import com.osh.communication.MessageBase;

import java.util.Map;

public class DoorUnlockMessage extends MessageBase {

    public static String DU_ATTRIB_STAGE = "stage";
    public static String DU_ATTRIB_DOOR_ID = "did";
    public static String DU_ATTRIB_TS = "ts";
    public static String DU_ATTRIB_OTH = "oth";
    public static String DU_ATTRIB_RESULT_HASH = "rh";

    enum DU_AUTH_STAGE {
        CHALLENGE_REQUESTED,
        CHALLENGE_CREATED,
        CHALLENGE_CALCULATED,
        CHALLENGE_SUCCESS,
        CHALLENGE_FAILURE
    };

    private String userId;
    private String doorId;
    private Map<String, Object> values;

    public DoorUnlockMessage(String userId, String doorId, Map<String, Object> values) {
        this.userId = userId;
        this.doorId = doorId;
        this.values = values;
    }

    public String getDoorId() {
        return doorId;
    }

    public String getUserId() {
        return userId;
    }

    public Map<String, Object> getValues() {
        return values;
    }

    @Override
    public MESSAGE_TYPE getMessageType() {
        return MESSAGE_TYPE.MESSAGE_TYPE_DOOR_UNLOCK;
    }

    @Override
    public String getFirstLevelId() {
        return userId;
    }

    @Override
    public String getSecondLevelId() {
        return doorId;
    }
}
