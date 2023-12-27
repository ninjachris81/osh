#ifndef OBISCONTROLLER2_H
#define OBISCONTROLLER2_H

#include <QObject>
#include <QProcess>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "controller/controllermessage.h"
#include "value/integervalue.h"

class SHARED_LIB_EXPORT OBISController2 : public ControllerBase
{
    Q_OBJECT
public:
    OBISController2(ControllerManager* manager, QString id, QObject *parent = nullptr);
    ~OBISController2();

    enum SML_INDEX {
        CONSUMPTION_TOTAL,
        PRODUCTION_TOTAL,


        COUNT
    };

    struct SML_DATA {
        SML_INDEX index;
        QVariant value;

        bool setIndex(QString data) {
            if (data == "1.8.0") {
                index = CONSUMPTION_TOTAL;
                return true;
            } else if (data == "2.8.0") {
                index = PRODUCTION_TOTAL;
                return true;
            }

            return false;
        }

        // should set index first before calling this
        void setValue(QString data) {
            switch(index) {
            case CONSUMPTION_TOTAL:
            case PRODUCTION_TOTAL:
                value = data.toInt();
                break;
            default:
                break;
            }
        }
    };

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    /*virtual*/ quint8 bindValue(ValueBase* value) override;


protected slots:
    void onProcessStarted();
    void onProcessFinished(int exitCode);
    void onDataReceived();

private:
    QProcess m_serverProcess;
    ValueManagerBase* m_valueManager;
    ClientSystemWarningsManager* m_warnManager;

    QList<ValueBase*> m_valueMappings;

    bool parseData(QString lineData, SML_DATA &data);

Q_SIGNALS:
    void dataReceived(SML_INDEX index, double value);

};

#endif // OBISCONTROLLER2_H
