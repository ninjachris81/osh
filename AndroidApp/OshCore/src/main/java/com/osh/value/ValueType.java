package com.osh.value;

public enum ValueType {
    VT_SWITCH(0),
    VT_BRIGHTNESS(1),
    VT_TEMP(2),
    VT_HUMIDITY(3),
    VT_MOTION(4),
    VT_WATER_FLOW(5),
    VT_TIMESTAMP(6),
    VT_RELAY_LIGHT(50),
    VT_RELAY_SHUTTER(51),
    VT_ALARM_SOUND(60),
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
