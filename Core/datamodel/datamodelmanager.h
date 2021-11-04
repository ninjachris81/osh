#ifndef DATAMODELMANAGER_H
#define DATAMODELMANAGER_H

#include <QObject>

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "datamodelloaderbase.h"
#include "datamodelbase.h"

class DatamodelManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DatamodelManager(QObject *parent = nullptr);

    static QString MANAGER_NAME;

    /*virtual*/ void init(LocalConfig* config);

    /*virtual*/ QString getName();

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType();

    /*virtual*/ void handleReceivedMessage(MessageBase* msg);

private:
    DatamodelLoaderBase* m_datamodelLoader = nullptr;
    DatamodelBase* m_datamodel = nullptr;

signals:

public slots:
};

#endif // DATAMODELMANAGER_H
