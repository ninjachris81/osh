
# Define all service dependencies
declare -A ALL_SERVICE_DEPENDENCIES=(
    ["AudioService"]="osh-qt6, postgresql-client, mpg123, libegl1, libfontconfig1, libxkbcommon0, libglx0, libopengl0"
    ["CoreService"]="osh-qt6, postgresql, mosquitto"
    ["DoorCameraService"]="osh-qt6, postgresql-client, livemedia-utils"
    ["GPIOInputService"]="osh-qt6, osh-wiringpi, postgresql-client, i2c-tools, libi2c-dev"
    ["RS232InputService"]="osh-qt6, postgresql-client"
    ["RS485EnergyMeterService"]="osh-qt6, postgresql-client"
    ["RS485RelayService"]="osh-qt6, postgresql-client"
    ["ShutterService"]="osh-qt6, postgresql-client"
    ["WBB12Service"]="osh-qt6, postgresql-client"
)

# Define all service scripts
declare -A ALL_SERVICE_SCRIPTS=(
    ["AudioService"]=""
    ["CoreService"]=""
    ["DoorCameraService"]=""
    ["GPIOInputService"]="raspi-config nonint do_i2c 0"
    ["RS232InputService"]=""
    ["RS485EnergyMeterService"]=""
    ["RS485RelayService"]=""
    ["ShutterService"]=""
    ["WBB12Service"]=""
)

# Define all service libraries
declare -A ALL_SERVICE_LIBRARIES=(
    ["AudioService"]="Core AudioController QMqttCommunicationManager"
    ["CoreService"]="Core CoreServer QMqttCommunicationManager"
    ["DoorCameraService"]="Core DoorCameraController QMqttCommunicationManager"
    ["GPIOInputService"]="Core GPIOInputController QMqttCommunicationManager"
    ["RS232InputService"]="Core CoreSerial RS232InputController QMqttCommunicationManager"
    ["RS485EnergyMeterService"]="Core CoreSerial RS485EnergyMeterController QMqttCommunicationManager"
    ["RS485RelayService"]="Core CoreSerial RS485RelayController QMqttCommunicationManager"
    ["ShutterService"]="Core ShutterController QMqttCommunicationManager"
    ["WBB12Service"]="Core CoreSerial WBB12Controller QMqttCommunicationManager"
)

declare -A SERVICE_DEPENDENCIES
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    echo "Processing dependencies for service $service"
    if [[ -v "ALL_SERVICE_DEPENDENCIES[$service]" ]]; then
        SERVICE_DEPENDENCIES["$service"]="${ALL_SERVICE_DEPENDENCIES[$service]}"
    else
        echo "No defined dependencies for service $service" >&2
        exit 4
    fi
done

declare -A SERVICE_SCRIPTS
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    if [[ -v "ALL_SERVICE_SCRIPTS[$service]" ]]; then
        SERVICE_SCRIPTS["$service"]="${ALL_SERVICE_SCRIPTS[$service]}"
    else
        echo "No defined scripts for service $service" >&2
        exit 4
    fi
done

declare -A SERVICE_LIBRARIES
for service in "${!SERVICE_EXECUTABLES[@]}"; do
    if [[ -v "ALL_SERVICE_LIBRARIES[$service]" ]]; then
        SERVICE_LIBRARIES["$service"]="${ALL_SERVICE_LIBRARIES[$service]}"
    else
        echo "No defined libraries for service $service" >&2
        exit 4
    fi
done

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_DEPENDENCIES[@]}" ]; then
    echo "Mismatch between number of service executables and their dependencies" >&2
    exit 4
fi

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_SCRIPTS[@]}" ]; then
    echo "Mismatch between number of service executables and their scripts" >&2
    exit 4
fi

if [ "${#SERVICE_EXECUTABLES[@]}" -ne "${#SERVICE_LIBRARIES[@]}" ]; then
    echo "Mismatch between number of service executables and their libraries" >&2
    exit 4
fi
