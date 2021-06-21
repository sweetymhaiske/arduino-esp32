#include "esp_system.h"
//#if ESP_IDF_VERSION_MAJOR >= 4 && CONFIG_ESP_RMAKER_TASK_STACK && CONFIG_IDF_TARGET_ESP32

#include <esp_rmaker_utils.h>

static void RMakerFactoryReset(int reset_seconds, int reboot_seconds)
{
    esp_rmaker_factory_reset(reset_seconds, reboot_seconds);
}

static void RMakerWiFiReset(int reset_seconds, int reboot_seconds)
{
    esp_rmaker_wifi_reset(reset_seconds, reboot_seconds);
}

//#endif
