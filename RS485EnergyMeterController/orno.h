#ifndef ORNOH_H
#define ORNOH_H

#include <QObject>

class OrnoWe : public QObject {
    Q_OBJECT

public:

    enum OrnoTypes {
        WE514,
        WE516
    };

    enum OrnoRegisters {
        FREQUENCY,

        VOLTAGE_P1,
        VOLTAGE_P2,
        VOLTAGE_P3,

        CURRENT_P1,
        CURRENT_P2,
        CURRENT_P3,

        POWER_P1,
        POWER_P2,
        POWER_P3,

        POWER_TOTAL,

        ENERGY_P1,
        ENERGY_P2,
        ENERGY_P3,

        ENERGY_TOTAL
    };
    Q_ENUM(OrnoRegisters)

    enum OrnoWe514_Input_Registers {
        WE514_COMM_ADDRESS = 0x110,
        WE514_COMM_BAUD_RATE = 0x111,

        WE514_FREQUENCY = 0x130,

        WE514_VOLTAGE_P1 = 0x131,
        WE514_VOLTAGE_P2 = 0x132,
        WE514_VOLTAGE_P3 = 0x133,

        WE514_CURRENT_P1 = 0x13A,
        WE514_CURRENT_P2 = 0x13C,
        WE514_CURRENT_P3 = 0x13E,

        WE514_POWER_P1 = 0x141,
        WE514_POWER_P2 = 0x142,
        WE514_POWER_P3 = 0x144,

        WE514_POWER_TOTAL = 0x146,

        WE514_ENERGY_TOTAL = 0xA000
    };
    Q_ENUM(OrnoWe514_Input_Registers)

    enum OrnoWe516_Input_Registers {
        WE516_FREQUENCY = 0x0014,

        WE516_VOLTAGE_P1 = 0x000E,
        WE516_VOLTAGE_P2 = 0x0010,
        WE516_VOLTAGE_P3 = 0x0012,

        WE516_CURRENT_P1 = 0x0016,
        WE516_CURRENT_P2 = 0x0018,
        WE516_CURRENT_P3 = 0x001A,

        WE516_POWER_P1 = 0x001E,
        WE516_POWER_P2 = 0x0020,
        WE516_POWER_P3 = 0x0022,

        WE516_POWER_TOTAL = 0x001C,

        WE516_ENERGY_TOTAL = 0x0100,
        WE516_ENERGY_P1 = 0x0102,
        WE516_ENERGY_P2 = 0x0104,
        WE516_ENERGY_P3 = 0x0106,
    };

    static float u2fA(uint16_t a, uint16_t b)
    {
      float result = 0;
      *(((uint16_t*)&result)+0) = a;
      *(((uint16_t*)&result)+1) = b;
      return result;
    }
};

#endif // ORNOH_H
