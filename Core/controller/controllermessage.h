#ifndef CONTROLLERMESSAGE_H
#define CONTROLLERMESSAGE_H

#include <QObject>
#include <QJsonDocument>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "communication/messagebase.h"
#include "shared/controllercmdtypes_qt.h"

class SHARED_LIB_EXPORT ControllerMessage : public MessageBase
{
    Q_OBJECT
public:

    ControllerBase::CONTROLLER_CMD_TYPE m_cmdType = ControllerBase::CCT_UNKNOWN;

    explicit ControllerMessage(QString controllerId, QVariantMap data, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString controllerId();

    QVariantMap data();

    ControllerBase::CONTROLLER_CMD_TYPE cmdType();

protected:
    QString m_controllerId;
    QVariantMap m_data;

signals:

public slots:
};

#endif // CONTROLLERMESSAGE_H
