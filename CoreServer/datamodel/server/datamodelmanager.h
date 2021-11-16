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

    static QLatin1Literal MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    DatamodelBase* datamodel();

private:
    DatamodelLoaderBase* m_datamodelLoader = nullptr;
    DatamodelBase* m_datamodel = nullptr;

signals:
    void datamodelChanged();

public slots:
};

#endif // DATAMODELMANAGER_H
