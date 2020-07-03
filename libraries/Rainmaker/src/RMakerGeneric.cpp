#include "RMakerGeneric.h"
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp32-hal.h>

void RMakerGenericClass::rmakerInit(char *node_name, char *node_type)
{
    esp_rmaker_config_t rainmaker_cfg = {
        .info = {
            .name = node_name,
            .type = node_type,
        },
        .enable_time_sync = false,
    };
    esp_err_t err = esp_rmaker_init(&rainmaker_cfg);
    if (err != ESP_OK) {
        log_e("Could not initialise ESP RainMaker. Aborting!!!");
        vTaskDelay(5000/portTICK_PERIOD_MS);
        abort();
    }
}

esp_err_t RMakerGenericClass::createDevice(const char *dev_name, const char *dev_type, DeviceParamCb cb, void *data)
{
    return esp_rmaker_create_device(dev_name, dev_type, cb, data);
}

esp_err_t RMakerGenericClass::deviceAssignPrimaryParam(const char *dev_name, const char *param_name)
{
    return esp_rmaker_device_assign_primary_param(dev_name, param_name);
}

//Parameter
esp_err_t RMakerGenericClass::deviceAddNameParam(const char *dev_name, const char *param_name)
{
    return esp_rmaker_device_add_name_param(dev_name, param_name);
}

esp_err_t RMakerGenericClass::deviceAddPowerParam(const char *dev_name, const char *param_name, bool val)
{
    return esp_rmaker_device_add_power_param(dev_name, param_name, val);
}

esp_err_t RMakerGenericClass::deviceAddBrightnessParam(const char *dev_name, const char *param_name, int val)
{
    return esp_rmaker_device_add_brightness_param(dev_name, param_name, val);
}

//update parameter
esp_err_t RMakerGenericClass::updateParam(const char *dev_name, const char *param_name, Param_t val)
{
    return esp_rmaker_update_param(dev_name, param_name, val);
}
