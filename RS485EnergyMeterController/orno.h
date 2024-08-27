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

    enum OrnoWe514_Input_Registers {
        WE514_COMM_ADDRESS = 0x110,
        WE514_COMM_BAUD_RATE = 0x111,

        WE514_FREQUENCY = 0x130,

        WE514_PHASE_VOLTAGE_V1 = 0x131,
        WE514_PHASE_VOLTAGE_V2 = 0x132,
        WE514_PHASE_VOLTAGE_V3 = 0x133,

        WE514_PHASE_CURRENT_I1 = 0x139,
        WE514_PHASE_CURRENT_I2 = 0x13b,
        WE514_PHASE_CURRENT_I3 = 0x13d,

        WE514_PHASE_ACTIVE_POWER_P1 = 0x140,
        WE514_PHASE_ACTIVE_POWER_P2 = 0x142,
        WE514_PHASE_ACTIVE_POWER_P3 = 0x144,

        WE514_TOTAL_ACTIVE_POWER = 0x146,
    };
    Q_ENUM(OrnoWe514_Input_Registers)

    enum OrnoWe516_Input_Registers {
        WE516_FREQUENCY = 0x9c55,

        WE516_PHASE_VOLTAGE_V1 = 0x9c4f,
        WE516_PHASE_VOLTAGE_V2 = 0x9c50,
        WE516_PHASE_VOLTAGE_V3 = 0x9c51,

        WE516_PHASE_CURRENT_I1 = 0x9c57,
        WE516_PHASE_CURRENT_I2 = 0x9c58,
        WE516_PHASE_CURRENT_I3 = 0x9c59,

        WE516_PHASE_ACTIVE_POWER_P1 = 0x9c5f,
        WE516_PHASE_ACTIVE_POWER_P2 = 0x9c60,
        WE516_PHASE_ACTIVE_POWER_P3 = 0x9c61,

        WE516_PHASE_ACTIVE_POWER = 0x9c5d,

        WE516_TOTAL_ACTIVE_ENERGY = 0x9c83,
        WE516_TOTAL_ACTIVE_ENERGY_P1 = 0x9c85,
        WE516_TOTAL_ACTIVE_ENERGY_P2 = 0x9c87,
        WE516_TOTAL_ACTIVE_ENERGY_P3 = 0x9c89,
    };
};

#endif // ORNOH_H
