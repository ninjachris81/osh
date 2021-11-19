#ifndef CONTROLLERCMDTYPES_QT_H
#define CONTROLLERCMDTYPES_QT_H

#include <QObject>
#include <QVariant>

#define USES_CONTROLLER_CMD_TYPES_QT

#include "constants.h"
#include "controllercmdtypes.h"

namespace controller {
Q_NAMESPACE

    enum CONTROLLER_CMD_TYPE {
        CCT_UNKNOWN = ENUM_UNKNOWN,
        CCT_ENABLE = CONTROLLER_CMD_TYPE_ENABLE,
    };

    Q_ENUM_NS(CONTROLLER_CMD_TYPE)
}

#endif // CONTROLLERCMDTYPES_QT_H
