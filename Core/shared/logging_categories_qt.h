#ifndef LOGGING_CATEGORIES_QT_H
#define LOGGING_CATEGORIES_QT_H

#include <QObject>
#include "logging_categories.h"

namespace LogCat {
Q_NAMESPACE

    static QString LOGGING_CATEGORIES[] = {
        LOGCAT_COMMON,
        LOGCAT_ACTOR,
        LOGCAT_COMMUNICATION,
        LOGCAT_CONTROLLER,
        LOGCAT_DEVICE,
        LOGCAT_LOG,
        LOGCAT_TIME,
        LOGCAT_VALUE,
        LOGCAT_WARN,
        LOGCAT_PROCESSOR,
        LOGCAT_DATAMODEL
    };

    enum LOGCAT {
        COMMON = 0,
        ACTOR,
        COMMUNICATION,
        CONTROLLER,
        DEVICE,
        LOG,
        TIME,
        VALUE,
        WARN,
        PROCESSOR,
        DATAMODEL
    };
    Q_ENUM_NS(LOGCAT)
}


#endif // LOGGING_CATEGORIES_QT_H
