#ifndef CONTROLLERMESSAGE_H
#define CONTROLLERMESSAGE_H

#include <QObject>
#include <QJsonDocument>

#include "communication/messagebase.h"
#include "shared/controllercmdtypes_qt.h"

using namespace controller;

class ControllerMessage : public MessageBase
{
    Q_OBJECT
public:
    CONTROLLER_CMD_TYPE m_cmdType = CCT_UNKNOWN;

    explicit ControllerMessage(QString controllerId, QVariantMap data, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString controllerId();

    QVariantMap data();

    CONTROLLER_CMD_TYPE cmdType();

protected:
    QString m_controllerId;
    QVariantMap m_data;

signals:

public slots:
};

#endif // CONTROLLERMESSAGE_H
