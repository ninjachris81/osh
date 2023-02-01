#ifndef MESSAGEBASE_H
#define MESSAGEBASE_H

#include <QObject>
#include <QVariant>

#include "sharedlib.h"

class SHARED_LIB_EXPORT MessageBase : public QObject
{
    Q_OBJECT
public:
    explicit MessageBase(QObject *parent = nullptr);

    enum MESSAGE_TYPE {
        MESSAGE_TYPE_UNKNOWN,
        MESSAGE_TYPE_VALUE,
        MESSAGE_TYPE_ACTOR,
        MESSAGE_TYPE_ACTOR_CONFIG,
        MESSAGE_TYPE_DEVICE_DISCOVERY,
        MESSAGE_TYPE_SYSTEM_TIME,
        MESSAGE_TYPE_SYSTEM_WARNING,
        MESSAGE_TYPE_CONTROLLER,
        MESSAGE_TYPE_LOG,
        MESSAGE_TYPE_SCRIPT_RESULT,
        MESSAGE_TYPE_DOOR_UNLOCK
    };
    Q_ENUM(MESSAGE_TYPE)

    virtual MESSAGE_TYPE getMessageType() = 0;

    virtual QString getFirstLevelId() = 0;

    virtual QString getSecondLevelId() = 0;

signals:

public slots:
};

#endif // MESSAGEBASE_H
