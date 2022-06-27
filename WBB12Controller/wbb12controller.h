#ifndef WBB12CONTROLLER_H
#define WBB12CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QModbusRtuSerialMaster>

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"

class WBB12Controller : public ControllerBase
{
    Q_OBJECT
public:
#define ERROR_CODE_NO_ERROR     65535

#define NO_ERROR_ERROR_ACTIVE   0
#define NO_ERROR_NO_ERROR       1

#define OPERATING_MODE_AUTO     0
#define OPERATING_MODE_HEATING  1
#define OPERATING_MODE_COOLING  2
#define OPERATING_MODE_SUMMER   3
#define OPERATING_MODE_STANDBY  4
#define OPERATING_MODE_2WEZ     5

    enum WBB12_Input_Registers {
        OUTSIDE_TEMP_1 = 0,
        OUTSIDE_TEMP_2 = 1,
        ERROR_CODE = 2,
        WARNING_CODE = 3,
        NO_ERROR = 4,
        OPERATING_DISPLAY = 5,

        HK1_ROOM_TARGET_TEMP = 1100,
        HK1_ROOM_TEMP = 1101,
        HK1_ROOM_HUMIDITY = 1102,
        HK1_FLOW_TARGET_TEMP = 1103,
        HK1_FLOW_TEMP = 1104,

        HK2_ROOM_TARGET_TEMP = 1200,
        HK2_ROOM_TEMP = 1201,
        HK2_ROOM_HUMIDITY = 1202,
        HK2_FLOW_TARGET_TEMP = 1203,
        HK2_FLOW_TEMP = 1204,

        WARM_WATER_TARGET_TEMP = 2100,
        WARM_WATER_TEMP = 2101,

        HEAT_PUMP_MODE = 3100,
        HEAT_PUMP_ERROR = 3101,
        HEAT_PUMP_CONSUMPTION = 3102,
        HEAT_PUMP_FLOW = 3103,
        HEAT_PUMP_RETURN_FLOW = 3104,

        HEAT_COIL_STATUS = 4100,
        HEAT_COIL_WORKING_HOURS = 4101,
        HEAT_COIL_SWITCH = 4102,
        HEAT_COIL_STATUS_COIL1 = 4103,
        HEAT_COIL_STATUS_COIL2 = 4104,
        HEAT_COIL_WORKING_HOURS_COIL1 = 4105,
        HEAT_COIL_WORKING_HOURS_COIL2 = 4106,

        ENERGY_TOTAL_TODAY = 6100,
        ENERGY_TOTAL_YESTERDAY = 6101,
        ENERGY_TOTAL_MONTH = 6102,
        ENERGY_TOTAL_YEAR = 6103,

        ENERGY_HEATING_TODAY = 6200,
        ENERGY_HEATING_YESTERDAY = 6201,
        ENERGY_HEATING_MONTH = 6202,
        ENERGY_HEATING_YEAR = 6203,

        ENERGY_WARM_WATER_TODAY = 6300,
        ENERGY_WARM_WATER_YESTERDAY = 6301,
        ENERGY_WARM_WATER_MONTH = 6302,
        ENERGY_WARM_WATER_YEAR = 6303,

        ENERGY_COOLING_TODAY = 6400,
        ENERGY_COOLING_YESTERDAY = 6401,
        ENERGY_COOLING_MONTH = 6402,
        ENERGY_COOLING_YEAR = 6403,
    };
    Q_ENUM(WBB12_Input_Registers)

    enum WBB12_Holdings {
        OPERATING_MODE = 0,
    };
    Q_ENUM(WBB12_Holdings)


    explicit WBB12Controller(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

protected slots:
    void onStateChanged();
    void onErrorOccurred();
    void onDataReceived();

    void retrieveStatus();

private:
    ClientSystemWarningsManager* m_warnManager;
    QModbusRtuSerialMaster m_modbusClient;
    QTimer m_statusTimer;
    int m_slaveId = 1;


signals:

};

#endif // WBB12CONTROLLER_H
