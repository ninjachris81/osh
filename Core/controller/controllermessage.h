#ifndef CONTROLLERMESSAGE_H
#define CONTROLLERMESSAGE_H

#include <QObject>
#include <QJsonDocument>

#include "communication/messagebase.h"
#include "shared/controllercmdtypes_qt.h"

class ControllerMessage : public MessageBase
{
    Q_OBJECT
public:
    CONTROLLER_CMD_TYPE m_cmdType = CCT_UNKNOWN;

    explicit ControllerMessage(QString controllerId, QVariant data, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType();

    /*virtual*/ QString getFirstLevelId();

    /*virtual*/ QString getSecondLevelId();

    QString controllerId();

    QVariant data();

    CONTROLLER_CMD_TYPE cmdType();

protected:
    QString m_controllerId;
    QVariant m_data;

signals:

public slots:
};

#endif // CONTROLLERMESSAGE_H
