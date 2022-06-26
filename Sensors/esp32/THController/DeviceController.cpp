#include "DeviceController.h"
#include "MQTTController.h"
#include "TaskIDs.h"
#include "TaskManager.h"
#include "shared/device.h"
#include "FlashController.h"

DeviceController::DeviceController(String deviceIdPrefix, String serviceIdPrefix) : AbstractIntervalTask(DEFAULT_DD_BROADCAST_INTERVAL), m_deviceIdPrefix(deviceIdPrefix), m_serviceIdPrefix(serviceIdPrefix) {
  
}

DeviceController::~DeviceController() {
}

void DeviceController::init() {
}

void DeviceController::update() {
  taskManager->getTask<MQTTController*>(MQTT_CONTROLLER)->publishSingleValue(BUILD_PATH(MQTT_MESSAGE_TYPE_DD + String(MQTT_PATH_SEP) + getDeviceId() + String(MQTT_PATH_SEP) + getServiceId()), (long) millis());
}

String DeviceController::getDeviceId() {
  return m_deviceIdPrefix + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex());
}

String DeviceController::getServiceId() {
  return m_serviceIdPrefix + String(taskManager->getTask<FlashController*>(FLASH_CONTROLLER)->getIndex());
}
