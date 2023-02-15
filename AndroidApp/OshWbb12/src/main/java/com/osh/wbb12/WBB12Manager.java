package com.osh.wbb12;

import com.osh.communication.MessageBase;
import com.osh.manager.IManagerRegistration;
import com.osh.manager.ManagerBase;
import com.osh.value.DoubleValue;
import com.osh.value.IValueManager;
import com.osh.value.IntegerValue;
import com.osh.value.ValueBase;
import com.osh.value.ValueGroup;
import com.osh.value.ValueType;

import org.apache.commons.lang3.StringUtils;
import org.apache.commons.text.CaseUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.LinkedHashMap;
import java.util.Set;

public class WBB12Manager extends ManagerBase implements IWBB12Manager {

    private static final Logger log = LoggerFactory.getLogger(WBB12Manager.class);

    private static final int WBB12_NoWarning = 65535;
    private static final int WBB12_Temperature_NoSensor = -32768;
    private static final int WBB12_Temperature_NoValue = -32767;

    public enum WBB12Unit {
        PlainInt,
        Temperature,
        KiloWattHours,
        Percentage,
        Warning,
        Enum,

        Special_
        ;

        public String withUnit(ValueBase value, Class<? extends Enum> enumHint) {
            if (value.getValue() == null) return "<null>";

            switch(this) {
                case Temperature:
                    if (value instanceof DoubleValue) {
                        if (((DoubleValue) value).getValue() == WBB12_Temperature_NoSensor) return "No sensor";
                        if (((DoubleValue) value).getValue() == WBB12_Temperature_NoValue) return "No value";
                    } else if (value instanceof IntegerValue) {
                        if (((IntegerValue) value).getValue() == WBB12_Temperature_NoSensor) return "No sensor";
                        if (((IntegerValue) value).getValue() == WBB12_Temperature_NoValue) return "No value";
                    }
                    return value.getValueAsString() + " °";
                case KiloWattHours:
                    return value.getValueAsString() + " kW/h";
                case Percentage:
                    return value.getValueAsString() + " %";
                case Warning:
                    int code = ((IntegerValue) value).getValue();
                    if (code == WBB12_NoWarning) return "None";
                    return "Code " + code;
                case Enum:
                    if (value instanceof IntegerValue && enumHint != null) {
                        Enum e = getEnumConstant(enumHint.getEnumConstants(), ((IntegerValue) value).getValue());
                        if (e == null) {
                            return "<invalid>";
                        } else {
                            return e.toString();
                        }
                    } else {
                        return value.getValueAsString();
                    }
                case PlainInt:
                    return value.getValueAsString();
                default:
                    return "";
            }
        }

        private Enum getEnumConstant(java.lang.Enum[] enumConstants, int value) {
            for (Enum enumConstant : enumConstants) {
                if (enumConstant instanceof WBB12_Enums.IWBB12EnumValueSupport) {
                    if (((WBB12_Enums.IWBB12EnumValueSupport) enumConstant).getValue() == value) return enumConstant;
                }
            }

            return null;
        }
    }

    public static class WBB12Format {
        private final boolean isWritable;
        private final WBB12Unit unit;

        private final Class<? extends Enum> enumType;

        public WBB12Format(boolean isWritable, WBB12Unit unit, Class <? extends Enum> enumType) {
            this.isWritable = isWritable;
            this.unit = unit;
            this.enumType = enumType;
        }

        public boolean isWritable() {
            return isWritable;
        }

        public WBB12Unit getUnit() {
            return unit;
        }

        public Class<? extends Enum> getEnumType() {
            return enumType;
        }
    }


    protected LinkedHashMap<String, WBB12Format> wbb12InputFormats = new LinkedHashMap<>();
    protected IValueManager valueManager;

    protected final ValueGroup wbb12ValueGroup = new ValueGroup("wbb12");

    @Override
    public Set<String> getWBB12Keys() {
        return wbb12InputFormats.keySet();
    }

    @Override
    public ValueBase getWBB12Value(String fullId) {
        return valueManager.getValue(fullId);
    }

    public WBB12Manager(IManagerRegistration managerRegistration, IValueManager valueManager) {
        super("WBB12Manager", managerRegistration);

        this.valueManager = valueManager;

        /*
        INPUTS
         */

        registerInputRegister(WBB12_Input_Registers.OUTSIDE_TEMP_1, WBB12Unit.Temperature, true);
        //registerInputRegister(WBB12_Input_Registers.OUTSIDE_TEMP_2, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.ERROR_CODE, WBB12Unit.Warning, false);
        registerInputRegister(WBB12_Input_Registers.WARNING_CODE, WBB12Unit.Warning, false);
        registerInputRegister(WBB12_Input_Registers.OPERATING_DISPLAY, WBB12Unit.Enum, false, WBB12_Enums.Enum_OPERATING_DISPLAY.class);

        registerInputRegister(WBB12_Input_Registers.HK1_ROOM_TARGET_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK1_ROOM_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK1_FLOW_TARGET_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK1_FLOW_TEMP, WBB12Unit.Temperature, true);

        registerInputRegister(WBB12_Input_Registers.HK3_ROOM_TARGET_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK3_ROOM_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK3_FLOW_TARGET_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HK3_FLOW_TEMP, WBB12Unit.Temperature, true);

        registerInputRegister(WBB12_Input_Registers.WARM_WATER_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.WARM_WATER_TARGET_TEMP, WBB12Unit.Temperature, true);

        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_MODE, WBB12Unit.Enum, false, WBB12_Enums.Enum_OPERATING_DISPLAY.class);
        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_ERROR, WBB12Unit.Warning, false);
        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_CONSUMPTION, WBB12Unit.Percentage, false);
        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_FLOW_TEMP, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_RETURN_FLOW_TEMP, WBB12Unit.Temperature, true);

        registerInputRegister(WBB12_Input_Registers.HEAT_COIL_STATUS, WBB12Unit.Enum, false, WBB12_Enums.Enum_STATUS.class);
        registerInputRegister(WBB12_Input_Registers.HEAT_COIL_STATUS_COIL1, WBB12Unit.Enum, false, WBB12_Enums.Enum_STATUS.class);
        registerInputRegister(WBB12_Input_Registers.HEAT_COIL_STATUS_COIL2, WBB12Unit.Enum, false, WBB12_Enums.Enum_STATUS.class);

        // stats
        registerInputRegister(WBB12_Input_Registers.ENERGY_TOTAL_TODAY, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_TOTAL_YESTERDAY, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_TOTAL_MONTH, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_TOTAL_YEAR, WBB12Unit.KiloWattHours, false);

        //registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_TODAY, WBB12Unit.KiloWattHours, false);

        /*
        HOLDINGS
         */

        registerHoldingRegister(WBB12_Holding_Registers.OPERATING_MODE, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_OPERATING_MODE.class);

        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_CONFIG, WBB12Unit.Enum, false, false, WBB12_Enums.Enum_HK_HEATING_CONFIG.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_DEMAND_TYPE, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_DEMAND_TYPE.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_OPERATING_MODE, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_OPERATING_MODE.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_PAUSE_PARTY, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_PAUSE_PARTY.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_TARGET_TEMP_COMFORT, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_TARGET_TEMP_NORMAL, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_TARGET_TEMP_REDUCE, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_CONSTANT_TEMP, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK1_HEATING_CONSTANT_TEMP_REDUCE, WBB12Unit.Temperature, true, true);

        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_CONFIG, WBB12Unit.Enum, false, false, WBB12_Enums.Enum_HK_HEATING_CONFIG.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_DEMAND_TYPE, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_DEMAND_TYPE.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_OPERATING_MODE, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_OPERATING_MODE.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_PAUSE_PARTY, WBB12Unit.Enum, false, true, WBB12_Enums.Enum_HK_HEATING_PAUSE_PARTY.class);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_TARGET_TEMP_COMFORT, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_TARGET_TEMP_NORMAL, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_TARGET_TEMP_REDUCE, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_CONSTANT_TEMP, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.HK3_HEATING_CONSTANT_TEMP_REDUCE, WBB12Unit.Temperature, true, true);

        registerHoldingRegister(WBB12_Holding_Registers.WARM_WATER_CONFIG, WBB12Unit.Enum, false, false, WBB12_Enums.Enum_WARM_WATER_CONFIG.class);
        registerHoldingRegister(WBB12_Holding_Registers.WARM_WATER_PUSH, WBB12Unit.Enum, false, true);
        registerHoldingRegister(WBB12_Holding_Registers.WARM_WATER_NORMAL, WBB12Unit.Temperature, true, true);
        registerHoldingRegister(WBB12_Holding_Registers.WARM_WATER_REDUCE, WBB12Unit.Temperature, true, true);

        registerHoldingRegister(WBB12_Holding_Registers.HEAT_PUMP_CONFIG, WBB12Unit.Enum, false, false, WBB12_Enums.Enum_HEAT_PUMP_CONFIG.class);
        registerHoldingRegister(WBB12_Holding_Registers.HEAT_PUMP_ACTIVATION_MODE, WBB12Unit.Enum, false, true);
        registerHoldingRegister(WBB12_Holding_Registers.HEAT_PUMP_WARM_WATER, WBB12Unit.Enum, false, true);
        registerHoldingRegister(WBB12_Holding_Registers.HEAT_PUMP_VOLUME_FLOW_HEATING, WBB12Unit.PlainInt, false, true);
        registerHoldingRegister(WBB12_Holding_Registers.HEAT_PUMP_VOLUME_FLOW_WARM_WATER, WBB12Unit.PlainInt, false, true);

    }

    @Override
    public MessageBase.MESSAGE_TYPE getMessageType() {
        return null;
    }

    @Override
    public void handleReceivedMessage(MessageBase msg) {
    }

    @Override
    public void initComplete() {
    }

    private void registerInputRegister(WBB12_Input_Registers reg, WBB12Unit unit, boolean isDouble) {
        if (unit == WBB12Unit.Enum) {
            log.warn("Should provide enum type");
        }
        registerInputRegister(reg, unit, isDouble, null);
    }

    private void registerInputRegister(WBB12_Input_Registers reg, WBB12Unit unit, boolean isDouble, Class<? extends Enum> enumType) {
        String mqttName = CaseUtils.toCamelCase(reg.toString(), false, '_');

        log.info("Registering WBB12 input " + mqttName);

        ValueBase val;
        if (isDouble) {
            val = new DoubleValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        } else {
            val = new IntegerValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        }

        if (wbb12InputFormats.containsValue(val.getFullId())) {
            throw new UnsupportedOperationException("Cannot register multiple times");
        }

        wbb12InputFormats.put(val.getFullId(), new WBB12Format(false, unit, enumType));
        valueManager.registerValue(val);

        val.addItemChangeListener(item -> {
            log.debug("WBB12 Value changed: " + item);
        });
    }

    private void registerHoldingRegister(WBB12_Holding_Registers reg, WBB12Unit unit, boolean isDouble, boolean canWrite) {
        if (unit == WBB12Unit.Enum) {
            log.warn("Should provide enum type");
        }
        registerHoldingRegister(reg, unit, isDouble, canWrite, null);
    }

    private void registerHoldingRegister(WBB12_Holding_Registers reg, WBB12Unit unit, boolean isDouble, boolean canWrite, Class<? extends Enum> enumType) {
        String mqttName = CaseUtils.toCamelCase(reg.toString(), false, '_');

        log.info("Registering WBB12 holding " + mqttName);

        ValueBase val;
        if (isDouble) {
            val = new DoubleValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        } else {
            val = new IntegerValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        }

        if (wbb12InputFormats.containsValue(val.getFullId())) {
            throw new UnsupportedOperationException("Cannot register multiple times");
        }

        wbb12InputFormats.put(val.getFullId(), new WBB12Format(canWrite, unit, enumType));
        valueManager.registerValue(val);

        val.addItemChangeListener(item -> {
            log.debug("WBB12 Value changed: " + item);
        });
    }

    @Override
    public WBB12Format getWBB12InputFormat(String fullId) {
        return wbb12InputFormats.get(fullId);
    }
}
