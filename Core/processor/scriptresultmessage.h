#ifndef SCRIPTRESULTMESSAGE_H
#define SCRIPTRESULTMESSAGE_H

#include <QObject>

#include "sharedlib.h"

#include "communication/messagebase.h"

class SHARED_LIB_EXPORT ScriptResultMessage : public MessageBase
{
    Q_OBJECT
public:
    explicit ScriptResultMessage(QString processorTaskId, QVariant value, QObject *parent = nullptr);

    /*virtual*/ MESSAGE_TYPE getMessageType() override;

    /*virtual*/ QString getFirstLevelId() override;

    /*virtual*/ QString getSecondLevelId() override;

    QString processorTaskId();

    QVariant value();

signals:

private:
    QString m_processorTaskId;
    QVariant m_value;

public slots:
};

#endif // SCRIPTRESULTMESSAGE_H
