package com.osh.value;

public enum ValueType {
    VT_BRIGHTNESS(1),
    VT_TEMP(2),
    VT_HUMIDITY(3),
    VT_MOTION(4),
    VT_WATER_FLOW(5),
    VT_TIMESTAMP(6),
    VT_SWITCH(10),
    VT_SHUTTER_CLOSE_STATE(30),
    VT_SHUTTER_TILT_STATE(31),
    VT_SHUTTER_MODE(32),
    VT_RELAY_LIGHT(50),
    VT_RELAY_SHUTTER(51),
    VT_RELAY_TEMP_VALVE(52),
    VT_RELAY_DOOR_OPEN(53),
    VT_AUDIO(60),
    VT_TYPE_AUDIO_VOLUME(61),
    VT_ALARM_SOUND(62),
    VT_DOOR_OPENER(70),
    VT_HEAT_PUMP_DATA(80),
    VT_VIRTUAL_ACTOR(90);

    private int value;
	ValueType(int value) {
        this.value = value;
	}

    public static ValueType of(int value) {
        for (ValueType vt : ValueType.values()) {
            if (vt.value == value) return vt;
        }

        return null;
    }
}
