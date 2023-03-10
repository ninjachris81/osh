package com.osh.value;

public class EnumValue extends IntegerValue {

    private final int enumCount;

    public EnumValue(ValueGroup valueGroup, String id, ValueType valueType, int enumCount) {
        super(valueGroup, id, valueType);
        this.enumCount = enumCount;
    }
}
