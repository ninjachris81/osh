#ifndef DATAMODELMANAGER_H
#define DATAMODELMANAGER_H

#include <QObject>

#include "sharedlib.h"

#include "manager/managerbase.h"
#include "communication/messagebase.h"
#include "datamodelloaderbase.h"
#include "datamodelbase.h"

class SHARED_LIB_EXPORT DatamodelManager : public ManagerBase
{
    Q_OBJECT
public:
    explicit DatamodelManager(QObject *parent = nullptr);

    static QLatin1String MANAGER_ID;

    /*virtual*/ LogCat::LOGCAT logCat() override;

    /*virtual*/ void init(LocalConfig* config) override;

    /*virtual*/ QString id() override;

    /*virtual*/ MessageBase::MESSAGE_TYPE getMessageType() override;

    /*virtual*/ void handleReceivedMessage(MessageBase* msg) override;

    DatamodelBase* datamodel();

    bool isLoaded();

    Q_INVOKABLE void save();

private:
    bool m_isLoaded = false;
    DatamodelLoaderBase* m_datamodelLoader = nullptr;
    DatamodelBase* m_datamodel = nullptr;

    void registerValues();
    void registerActors();

private slots:
    void onDatamodelSaved();
    void onDatamodelError(QString desc);

signals:
    void datamodelChanged();

public slots:
};

#endif // DATAMODELMANAGER_H
