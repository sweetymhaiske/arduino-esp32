#include "RMakerGeneric.h"

#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp32-hal.h>

//Device API's
esp_err_t RMakerGenericClass::createDevice(const char *dev_name, const char *dev_type, DeviceParamCb cb, void *priv_data)
{
    device_name = dev_name;
    return esp_rmaker_create_device(dev_name, dev_type, cb, priv_data);
}

esp_err_t RMakerGenericClass::addDeviceAttr(const char *attr_name, const char *val)
{
    return esp_rmaker_device_add_attribute(device_name, attr_name, val);
}

esp_err_t RMakerGenericClass::addDeviceParam(const char *param_name, esp_rmaker_param_val_t val, uint8_t properties)
{
    return esp_rmaker_device_add_param(device_name, param_name, val, properties);
}

esp_err_t RMakerGenericClass::assignPrimaryParam(const char *param_name)
{
    return esp_rmaker_device_assign_primary_param(device_name, param_name);
}

//Service API's
esp_err_t RMakerGenericClass::createService(const char *serv_name, const char *type, DeviceParamCb cb, void *priv_data)
{
    return esp_rmaker_create_service(serv_name, type, cb, priv_data);
}

esp_err_t RMakerGenericClass::addServiceParam(const char *serv_name, const char *param_name, esp_rmaker_param_val_t val, uint8_t properties)
{
    return esp_rmaker_service_add_param(serv_name, param_name, val, properties);
}

//Device Parameter
esp_err_t RMakerGenericClass::addNameParam(const char *param_name)
{
    return esp_rmaker_device_add_name_param(device_name, param_name);
}

esp_err_t RMakerGenericClass::addPowerParam(bool val, const char *param_name)
{
    return esp_rmaker_device_add_power_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addBrightnessParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_brightness_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addHueParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_hue_param(device_name, param_name, val); 
}

esp_err_t RMakerGenericClass::addSaturationParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_saturation_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addIntensityParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_intensity_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addCctParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_cct_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addDirectionParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_direction_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addSpeedParam(int val, const char *param_name)
{
    return esp_rmaker_device_add_speed_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::addTempratureParam(float val, const char *param_name)
{
    return esp_rmaker_device_add_temperature_param(device_name, param_name, val);
}

//Service parameter
esp_err_t RMakerGenericClass::addOTAStatusParam(const char *serv_name, const char *param_name)
{
    return esp_rmaker_service_add_ota_status_param(serv_name, param_name);
}

esp_err_t RMakerGenericClass::addOTAInfoParam(const char *serv_name, const char *param_name)
{
    return esp_rmaker_service_add_ota_info_param(serv_name, param_name);
}

esp_err_t RMakerGenericClass::addOTAUrlParam(const char *serv_name, const char *param_name)
{
    return esp_rmaker_service_add_ota_url_param(serv_name, param_name);
}

//update device parameter
esp_err_t RMakerGenericClass::updateParam(const char *param_name, Param_t val)
{
    return esp_rmaker_update_param(device_name, param_name, val);
}

esp_err_t RMakerGenericClass::paramAddUIType(const char *name, const char *ui_type)
{
    return esp_rmaker_param_add_ui_type(device_name, name, ui_type);
}

esp_err_t RMakerGenericClass::paramAddBounds(const char *param_name, esp_rmaker_param_val_t min, esp_rmaker_param_val_t max, esp_rmaker_param_val_t step)
{
    return esp_rmaker_param_add_bounds(device_name, param_name, min, max, step);
}

esp_err_t RMakerGenericClass::paramAddType(const char *param_name, const char* type)
{
    return esp_rmaker_param_add_type(device_name, param_name, type);
}
