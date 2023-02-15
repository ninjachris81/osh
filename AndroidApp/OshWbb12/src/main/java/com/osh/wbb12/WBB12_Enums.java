package com.osh.wbb12;

public class WBB12_Enums {

    public interface IWBB12EnumValueSupport {

        int getValue();

    }

    public enum Enum_OPERATING_MODE implements IWBB12EnumValueSupport {
        AUTO(0),
        HEATING(1),
        COOLING(2),
        SUMMER(3),
        STANDBY(4),
        HEAT_COIL(5)
        ;


        private int value;
        Enum_OPERATING_MODE(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_OPERATING_DISPLAY implements IWBB12EnumValueSupport {
        UNDEFINED(0),
        RELAIS_TEST(1),
        EMERGENCY_OFF(2),
        DIAG(3),
        MANUAL_MODE(4),
        MANUAL_HEATING(5),
        MANUAL_COOLING(6),
        MANUAL_DEICE(7),
        DEICE(8),
        HEAT_COIL(9),
        EVU_BLOCK(10),
        SG_TARIF(11),
        SG_MAX(12),
        RATE_LOADING(13),
        INCREASED_OPERATION(14),
        IDLE(15),
        STANDBY(16),
        FLUSHING(17),
        ICE_PROTECTION(18),
        HEATING(19),
        WARM_WATER(20),
        LEGIONELLA_PROTECTION(21),
        SWITCH_HZKU(22),
        COOLING(23),
        PASSIVE_COOLING(24),
        SUMMER_MODE(25),
        POOL(26),
        VACATION(27),
        FLOOR(28),
        BLOCKED(29),
        BLOCK_AT(30),
        BLOCK_SUMMER(31),
        BLOCK_WINTER(32),
        LIMIT(33),
        HK_BLOCK(34),
        REDUCTION(35)
        ;


        private int value;
        Enum_OPERATING_DISPLAY(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_STATUS implements IWBB12EnumValueSupport {
        OFF(0),
        ON(1),
        ;


        private int value;
        Enum_STATUS(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_HK_HEATING_CONFIG implements IWBB12EnumValueSupport {
        OFF(0),
        PUMP_CYCLE(1),
        MIX_CYCLE(2),
        TARGET_TEMP(3)
        ;


        private int value;
        Enum_HK_HEATING_CONFIG(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_HK_HEATING_DEMAND_TYPE implements IWBB12EnumValueSupport {
        OFF(0),
        WEATHER_DRIVEN(1),
        CONSTANT(2),
        ;


        private int value;
        Enum_HK_HEATING_DEMAND_TYPE(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_HK_HEATING_OPERATING_MODE implements IWBB12EnumValueSupport {
        AUTO(0),
        COMFORT(1),
        NORMAL(2),
        REDUCE(3),
        STANDBY(4)
        ;


        private int value;
        Enum_HK_HEATING_OPERATING_MODE(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_HK_HEATING_PAUSE_PARTY implements IWBB12EnumValueSupport {
        PAUSE_12H(1),
        PAUSE_11_5H(2),
        PAUSE_11H(3),
        PAUSE_10_5H(4),
        PAUSE_10H(5),
        PAUSE_9_5H(6),
        PAUSE_9H(7),
        PAUSE_8_5H(8),
        PAUSE_8H(9),
        PAUSE_7_5H(10),
        PAUSE_7H(11),
        PAUSE_6_5H(12),
        PAUSE_6H(13),
        PAUSE_5_5H(14),
        PAUSE_5H(15),
        PAUSE_4_5H(16),
        PAUSE_4H(17),
        PAUSE_3_5H(18),
        PAUSE_3H(19),
        PAUSE_2_5H(20),
        PAUSE_2H(21),
        PAUSE_1_5H(22),
        PAUSE_1H(23),
        PAUSE_0_5H(24),
        AUTO(25),
        PARTY_0_5H(26),
        PARTY_1H(27),
        PARTY_12H(49)
        ;


        private int value;
        Enum_HK_HEATING_PAUSE_PARTY(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }


    public enum Enum_WARM_WATER_CONFIG implements IWBB12EnumValueSupport {
        AUTO(0),
        BYPASS_VALVE(1),
        PUMP(8),
        ;


        private int value;
        Enum_WARM_WATER_CONFIG(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

    public enum Enum_HEAT_PUMP_CONFIG implements IWBB12EnumValueSupport {
        TBD0(0),
        TBD1(1),
        TBD2(2),
        TBD3(3),
        TBD4(4),
        ;


        private int value;
        Enum_HEAT_PUMP_CONFIG(int value) {
            this.value = value;
        }

        @Override
        public int getValue() {
            return value;
        }
    }

}
