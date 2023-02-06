#ifndef WBB12CONTROLLER_H
#define WBB12CONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QModbusTcpClient>

#include "sharedlib.h"

#include "controller/controllerbase.h"
#include "warn/client/clientsystemwarningsmanager.h"
#include "value/valuemanagerbase.h"

class SHARED_LIB_EXPORT WBB12Controller : public ControllerBase
{
    Q_OBJECT
public:

    static int WBB12_Input_Registers_Offset;

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

    enum WBB12_ConfigHP {
        WFDE_ConfigHP_NotConfigured,
        WFDE_ConfigHP_HeatingAvailable,
        WFDE_ConfigHP_HeatingCoolingAvailable
    };
    Q_ENUM(WBB12_ConfigHP)

    enum WBB12_ConfigHeating {
        WFDE_ConfigHeating_HeatingNotConfigured,
        WFDE_ConfigHeating_DemandRoomControl,
        WFDE_ConfigHeating_DemandConstantControl,
        WFDE_ConfigHeating_DemandWeatherControl
    };

    enum WBB12_StatusHeating {
        WFDE_StatusHeating_Off,
        WFDE_StatusHeating_HeatingActive,
        WFDE_StatusHeating_CoolingActive,
        WFDE_StatusHeating_HeatingBlocked,
        WFDE_StatusHeating_CoolingBlocked
    };

    enum WBB12_AllowanceStatusHP {
        WFDE_AllowanceStatusHP_Off,
        WFDE_AllowanceStatusHP_OnlyHeating,
        WFDE_AllowanceStatusHP_OnlyCooling,
        WFDE_AllowanceStatusHP_HeatingCoolingAllowed
    };

    enum WBB12_ConfigWarmWater {
        WFDE_ConfigWarmWater_Blocked,
        WFDE_ConfigWarmWater_WithTargetValue
    };

    enum WBB12_StatusWarmWater {
        WFDE_StatusWarmWater_Off,
        WFDE_StatusWarmWater_NoDemand,
        WFDE_StatusWarmWater_LoadingPriority,
        WFDE_StatusWarmWater_LoadingParallel,
        WFDE_StatusWarmWater_DemandActiveLoadingBlocked
    };

    static signed short WFDE_TargetValue_NotAvailable;
    static signed short WFDE_TargetValue_Off;

    enum WBB12_EEZOperationStatus {
        WFDE_EZOperationStatus_Heating,
        WFDE_EZOperationStatus_Warmwater,
        WFDE_EZOperationStatus_Pool,
        WFDE_EZOperationStatus_EVUBlock,
        WFDE_EZOperationStatus_Deice,
        WFDE_EZOperationStatus_Standby,
        WFDE_EZOperationStatus_ExternalEnergy,
        WFDE_EZOperationStatus_Cooling
    };

    static signed short WFDE_Temperature_NoSensor;
    static signed short WFDE_Temperature_NoValue;

    enum WBB12_Status {
        WFDE_Status_Off,
        WFDE_Status_On
    };

    enum WBB12_OperationStatus {
        WFDE_OperationStatus_Undefined,
        WFDE_OperationStatus_RelaisTest,
        WFDE_OperationStatus_EmergencyOff,
        WFDE_OperationStatus_Diagnosis,
        WFDE_OperationStatus_HandMode,
        WFDE_OperationStatus_HandModeHeating,
        WFDE_OperationStatus_HandModeCooling,
        WFDE_OperationStatus_ManualDeice,
        WFDE_OperationStatus_Deice,
        WFDE_OperationStatus_WEZ2,
        WFDE_OperationStatus_EVUBlock,
        WFDE_OperationStatus_SGTarif,
        WFDE_OperationStatus_SGMaximal,
        WFDE_OperationStatus_RateLoading,
        WFDE_OperationStatus_IncreasedOperation,
        WFDE_OperationStatus_Idle,
        WFDE_OperationStatus_Standby,
        WFDE_OperationStatus_Flushing,
        WFDE_OperationStatus_IceProtection,
        WFDE_OperationStatus_Heating,
        WFDE_OperationStatus_WarmWater,
        WFDE_OperationStatus_LegionellaProtection,
        WFDE_OperationStatus_SwitchHZKU,
        WFDE_OperationStatus_Cooling,
        WFDE_OperationStatus_PassiveCooling,
        WFDE_OperationStatus_SummerMode,
        WFDE_OperationStatus_Pool,
        WFDE_OperationStatus_Vacation,
        WFDE_OperationStatus_Floor,
        WFDE_OperationStatus_Blocked,
        WFDE_OperationStatus_BlockAT,
        WFDE_OperationStatus_Summer,
        WFDE_OperationStatus_Winter,
        WFDE_OperationStatus_Limit,
        WFDE_OperationStatus_HKBlock,
        WFDE_OperationStatus_Reduction
    };

    enum WBB12_DataFormat {
        WDF_ConfigHP,
        WDF_ConfigHeating,
        WDF_StatusHeating,
        WDF_AllowanceStatusHP,
        WDF_ConfigWarmWater,
        WDF_StatusWarmWater,
        WDF_TargetValue,
        WDF_EEZOperationStatus,
        WDF_Temperature,
        WDF_Warning,
        WDF_Blocking,
        WDF_Locking,
        WDF_Status,
        WDF_Count,
        WDF_Version,
        WDF_ConfigRoom,
        WDF_OperationStatus,
    };

    struct RetrieveValue {
        uint16_t retrieveInterval;
        QVariant::Type type;
        WBB12_DataFormat dataFormat;
        QString mqttName;
    };


    explicit WBB12Controller(ControllerManager* manager, QString id, QObject *parent = nullptr);

    /*virtual*/ void init() override;

    /*virtual*/ void start() override;

    /*virtual*/ void handleMessage(ControllerMessage *msg) override;

    void bindValueManager(ValueManagerBase* valueManager);

protected slots:
    void onStateChanged();
    void onErrorOccurred();

    void retrieveStatus();

private:
    void registerInput(WBB12_Input_Registers reg, uint16_t retrieveInterval, QVariant::Type type, WBB12_DataFormat dataFormat, QString mqttName);
    void _readInput(WBB12_Input_Registers reg, RetrieveValue val);
    QVariant parseValue(int rawValue, WBB12_DataFormat format);

    QMap<WBB12_Input_Registers, RetrieveValue> m_inputRegisters;
    QMap<WBB12_Input_Registers, ValueBase*> m_valueMappings;

    ClientSystemWarningsManager* m_warnManager;
    QModbusTcpClient m_modbusClient;
    QTimer m_statusTimer;
    int m_slaveId = 1;

    ValueManagerBase* m_valueManager = nullptr;


signals:

};

#endif // WBB12CONTROLLER_H
