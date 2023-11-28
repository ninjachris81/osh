#ifndef ORNO_WE_514_H
#define ORNO_WE_514_H

#include <QObject>

class OrnoWe514 : public QObject {
    Q_OBJECT

public:
    enum OrnoWe514_Input_Registers {
        COMM_ADDRESS = 0x110,
        COMM_BAUD_RATE = 0x111,

        FREQUENCY = 0x130,

        PHASE_VOLTAGE_V1 = 0x131,
        PHASE_VOLTAGE_V2 = 0x132,
        PHASE_VOLTAGE_V3 = 0x133,

        PHASE_CURRENT_I1 = 0x139,
        PHASE_CURRENT_I2 = 0x13b,
        PHASE_CURRENT_I3 = 0x13d,

        PHASE_ACTIVE_POWER_P1 = 0x140,
        PHASE_ACTIVE_POWER_P2 = 0x142,
        PHASE_ACTIVE_POWER_P3 = 0x144,

        TOTAL_ACTIVE_POWER = 0x146,
    };
    Q_ENUM(OrnoWe514_Input_Registers)
};

#endif // ORNO_WE_514_H
