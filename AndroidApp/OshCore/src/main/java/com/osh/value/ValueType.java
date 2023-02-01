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
    VT_ALARM_SOUND(60);

	ValueType(int value) {
	}
}
