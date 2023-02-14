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

import org.apache.commons.text.CaseUtils;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.HashMap;
import java.util.Map;
import java.util.Set;

public class WBB12Manager extends ManagerBase implements IWBB12Manager {

    private static final Logger log = LoggerFactory.getLogger(WBB12Manager.class);

    public enum WBB12Unit {
        PlainInt,
        Temperature,
        KiloWattHours,
        Percentage,
        Enum;

        public String getAppendix(boolean withSpace) {
            switch(this) {
                case Temperature:
                    return wrapSpace("°", withSpace);
                case KiloWattHours:
                    return wrapSpace("kW/h", withSpace);
                case Percentage:
                    return wrapSpace("%", withSpace);
                default:
                    return "";
            }
        }

        public static String wrapSpace(String input, boolean withSpace) {
            return (withSpace ? " " : "") + input;
        }
    }

    public static class WBB12Format {
        private boolean isWritable = false;
        private WBB12Unit unit = WBB12Unit.PlainInt;

        public WBB12Format(boolean isWritable, WBB12Unit unit) {
            this.isWritable = isWritable;
            this.unit = unit;
        }

        public boolean isWritable() {
            return isWritable;
        }

        public WBB12Unit getUnit() {
            return unit;
        }
    }


    protected Map<String, WBB12Format> wbb12InputFormats = new HashMap<>();
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

        registerInputRegister(WBB12_Input_Registers.WARM_WATER_TEMP, false, WBB12Unit.Temperature, true);
        registerInputRegister(WBB12_Input_Registers.WARM_WATER_TARGET_TEMP, false, WBB12Unit.Temperature, true);

        registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_TODAY, false, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_YESTERDAY, false, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_MONTH, false, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_YEAR, false, WBB12Unit.KiloWattHours, false);

        registerInputRegister(WBB12_Input_Registers.ENERGY_HEATING_TODAY, false, WBB12Unit.KiloWattHours, false);
        registerInputRegister(WBB12_Input_Registers.HEAT_PUMP_CONSUMPTION, false, WBB12Unit.Percentage, false);
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

    private void registerInputRegister(WBB12_Input_Registers reg, boolean isWritable, WBB12Unit unit, boolean isDouble) {
        String mqttName = CaseUtils.toCamelCase(reg.toString(), false, '_');

        log.info("Registering WBB12 input " + mqttName);

        ValueBase val;
        if (isDouble) {
            val = new DoubleValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        } else {
            val = new IntegerValue(wbb12ValueGroup, mqttName, ValueType.VT_HEAT_PUMP_DATA);
        }

        wbb12InputFormats.put(val.getFullId(), new WBB12Format(isWritable, unit));
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
