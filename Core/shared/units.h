#ifndef UNITS_H
#define UNITS_H

#ifdef QT_VERSION
    #ifndef USES_UNITS_QT
        #error Should use Qt version
    #endif
#endif

#define UNIT_TYPE_DEGREES   1
#define UNIT_TYPE_PERCENT   2
#define UNIT_TYPE_TIMESTAMP 3


#endif // UNITS_H
