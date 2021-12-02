#include "DeviceController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include "shared/device.h"

DeviceController::DeviceController(String id, String serviceId) : AbstractIntervalTask(DEFAULT_DD_BROADCAST_INTERVAL), m_id(id), m_serviceId(serviceId) {
  
}

DeviceController::~DeviceController() {
}

void DeviceController::init() {
}

void DeviceController::update() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publish(BUILD_PATH(MQTT_MESSAGE_TYPE_DD + String(MQTT_PATH_SEP) + m_id + String(MQTT_PATH_SEP) + m_serviceId));
}
