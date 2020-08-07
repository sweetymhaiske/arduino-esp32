#include "RMakerGeneric.h"
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp32-hal.h>
#define PARMAS 13
esp_rmaker_param_t *assign[PARAMS];
esp_err_t err;

esp_rmaker_param_t *getParamHandle(const char *param_name)
{
    if(param_name == ESP_RMAKER_DEF_NAME_PARAM) {
        return assign[NAME_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_POWER_NAME) {
        return assign[POWER_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_BRIGHTNESS_NAME) {
        return assign[BRIGHTNESS_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_HUE_NAME) {
        return assign[HUE_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_SATURATION_NAME) {
        return assign[SATURATION_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_INTENSITY_NAME) {
        return assign[INTENSITY_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_CCT_NAME) {
        return assign[CCT_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_DIRECTION_NAME) {
        return assign[DIRECTION_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_SPEED_NAME) {
        return assign[SPEED_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_TEMPERATURE_NAME) {
        return assign[TEMPERATURE_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_OTA_STATUS_NAME) {
        return assign[STATUS_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_OTA_INFO_NAME) {
        return assign[INFO_PARAM];
    } else if(param_name == ESP_RMAKER_DEF_OTA_URL_NAME) {
        return assign[URL_PARAM];
    }   
}

void RMakerGenericClass::addCb(deviceWriteCb write_cb, deviceReadCb read_cb)
{
    esp_rmaker_device_add_cb(getDeviceHandle(), write_cb, read_cb);
}

void RMakerGenericClass::deleteDevice()
{
    err = esp_rmaker_device_delete(getDeviceHandle());
    if(err != ESP_OK) {
        log_e("Device Deletion error");
    }  
}

esp_err_t RMakerGenericClass::addDeviceAttr(const char *attr_name, const char *val)
{
    return esp_rmaker_device_add_attribute(getDeviceHandle(), attr_name, val);
}

void RMakerGenericClass::assignPrimaryParam(char *param_name)
{
    if(param_name == ESP_RMAKER_DEF_NAME_PARAM) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[NAME_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_POWER_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[POWER_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_BRIGHTNESS_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[BRIGHTNESS_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_HUE_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[HUE_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_SATURATION_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[SATURATION_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_INTENSITY_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[INTENSITY_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_CCT_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[CCT_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_DIRECTION_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[DIRECTION_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_SPEED_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[SPEED_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_TEMPERATURE_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[TEMPERATURE_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_STATUS_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[STATUS_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_INFO_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[INFO_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_URL_NAME) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), assign[URL_PARAM]);
    }
}

//Device Parameter
esp_err_t RMakerGenericClass::addNameParam(const char *param_name)
{
    assign[NAME_PARAM] = esp_rmaker_name_param_create(param_name, getDeviceName());
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[NAME_PARAM]);
}

esp_err_t RMakerGenericClass::addPowerParam(bool val, const char *param_name)
{
    assign[POWER_PARAM] = esp_rmaker_power_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[POWER_PARAM]);
}

esp_err_t RMakerGenericClass::addBrightnessParam(int val, const char *param_name)
{
    assign[BRIGHTNESS_PARAM] = esp_rmaker_brightness_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[BRIGHTNESS_PARAM]);
}

esp_err_t RMakerGenericClass::addHueParam(int val, const char *param_name)
{
    assign[HUE_PARAM] = esp_rmaker_hue_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[HUE_PARAM]);

}

esp_err_t RMakerGenericClass::addSaturationParam(int val, const char *param_name)
{
    assign[SATURATION_PARAM] = esp_rmaker_saturation_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[SATURATION_PARAM]);
}

esp_err_t RMakerGenericClass::addIntensityParam(int val, const char *param_name)
{
    assign[INTENSITY_PARAM] = esp_rmaker_intensity_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[INTENSITY_PARAM]);
}

esp_err_t RMakerGenericClass::addCctParam(int val, const char *param_name)
{
    assign[CCT_PARAM] = esp_rmaker_cct_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[CCT_PARAM]);
}

esp_err_t RMakerGenericClass::addDirectionParam(int val, const char *param_name)
{
    assign[DIRECTION_PARAM] = esp_rmaker_direction_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[DIRECTION_PARAM]);
}

esp_err_t RMakerGenericClass::addSpeedParam(int val, const char *param_name)
{
    assign[SPEED_PARAM] = esp_rmaker_speed_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[SPEED_PARAM]);
}

esp_err_t RMakerGenericClass::addTempratureParam(float val, const char *param_name)
{
    assign[TEMPERATURE_PARAM] = esp_rmaker_temperature_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[TEMPERATURE_PARAM]);

}

//Service parameter
esp_err_t RMakerGenericClass::addOTAStatusParam(const char *param_name)
{
    assign[STATUS_PARAM] = esp_rmaker_ota_status_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[STATUS_PARAM]);
}

esp_err_t RMakerGenericClass::addOTAInfoParam(const char *param_name)
{
    assign[INFO_PARAM] = esp_rmaker_ota_info_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[INFO_PARAM]);
}

esp_err_t RMakerGenericClass::addOTAUrlParam(const char *param_name)
{
    assign[URL_PARAM] = esp_rmaker_ota_url_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), assign[URL_PARAM]);
}

