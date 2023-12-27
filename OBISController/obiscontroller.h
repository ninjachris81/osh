#ifndef OBISCONTROLLER_H
#define OBISCONTROLLER_H

#include <QObject>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "serialportclient.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "controller/controllermessage.h"
#include "smlparser.h"
#include "value/integervalue.h"

class SHARED_LIB_EXPORT OBISController : public ControllerBase
{
    Q_OBJECT
public:
    OBISController(ControllerManager* manager, QString id, QObject *parent = nullptr);

    enum SML_INDEX {
        CONSUMPTION_TOTAL,
        PRODUCTION_TOTAL,


        COUNT
    };

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    double value(SML_INDEX smlIndex);

    /*virtual*/ quint8 bindValue(ValueBase* value) override;


protected slots:
    void onSerialConnected();
    void onSerialDisconnected();
    void onSerialDataReceived(QByteArray data);

    void onDataReceived(SML_INDEX index);

private:
    SmlParser m_smlParser;
    ValueManagerBase* m_valueManager;
    ClientSystemWarningsManager* m_warnManager;
    SerialPortClient* m_serialClient;

    QList<ValueBase*> m_valueMappings;
    bool m_startReceived = false;

    double m_values[SML_INDEX::COUNT];

Q_SIGNALS:
    void dataReceived(SML_INDEX index);

};

#endif // OBISCONTROLLER_H
