#ifndef UNITS_QT_H
#define UNITS_QT_H

#include <QObject>

#define USES_UNITS_QT

#include "constants.h"
#include "units.h"

namespace unit {
Q_NAMESPACE

    enum UNIT_TYPE {
        UT_UNKNOWN = ENUM_UNKNOWN,
        UT_DEGREES = UNIT_TYPE_DEGREES,
        UT_PERCENT = UNIT_TYPE_PERCENT,
        UT_TIMESTAMP = UNIT_TYPE_TIMESTAMP,
        UT_LITER_PER_MIN = UNIT_TYPE_LITER_PER_MIN
    };

    Q_ENUM_NS(UNIT_TYPE)
}



#endif // UNITS_QT_H
