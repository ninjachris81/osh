#ifndef ORNO_WE_514_H
#define ORNO_WE_514_H

#include <QObject>

class OrnoWe514 : public QObject {
    Q_OBJECT

public:
    enum OrnoWe514_Input_Registers {
        FREQUENCY = 130,

        PHASE_VOLTAGE_V1 = 131,
        PHASE_VOLTAGE_V2 = 132,
        PHASE_VOLTAGE_V3 = 133,

        PHASE_CURRENT_I1 = 139,
        PHASE_CURRENT_I2 = 140,
        PHASE_CURRENT_I3 = 141,
    };
    Q_ENUM(OrnoWe514_Input_Registers)
};

#endif // ORNO_WE_514_H
