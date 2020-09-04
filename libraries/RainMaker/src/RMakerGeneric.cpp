//#include "RMakerGeneric.h"
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp32-hal.h>
#include "RMaker.h"
extern RMakerClass RMaker;
static esp_err_t err;
void (*write_cb)(const char*, const char*, param_val_t, void*, write_ctx_t*);
void (*read_cb)(const char*, const char*, void*, read_ctx_t*);

static esp_err_t write_callback(const device_handle_t *device, const param_handle_t *param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    char *param_name = esp_rmaker_param_get_name(param);
    char *device_name = esp_rmaker_device_get_name(device);
    write_cb(device_name, param_name, val, priv_data, ctx);
    if(RMaker.getUpdateParam() == true) {
        esp_rmaker_param_update_and_report(param, val);
    }
    return ESP_OK;
}

static esp_err_t read_callback(const device_handle_t *device, const param_handle_t *param, void *priv_data, read_ctx_t *ctx)
{
    char *param_name = esp_rmaker_param_get_name(param);
    char *device_name = esp_rmaker_device_get_name(device);
    read_cb(device_name, param_name, priv_data, ctx);
    return ESP_OK;
}

esp_err_t RMakerGenericClass::deleteDevice()
{
    err = esp_rmaker_device_delete(getDeviceHandle());
    if(err != ESP_OK) {
        log_e("Device deletion error");
        return err;
    }  
    return ESP_OK;
}

void RMakerGenericClass::addCb(deviceWriteCb writeCb, deviceReadCb readCb)
{
    write_cb = writeCb;
    read_cb = readCb;
    err = esp_rmaker_device_add_cb(getDeviceHandle(), write_callback, read_callback);
    if(err != ESP_OK) {
        log_e("Callback register error");
    }
}

esp_err_t RMakerGenericClass::addDeviceAttr(const char *attr_name, const char *val)
{
    err = esp_rmaker_device_add_attribute(getDeviceHandle(), attr_name, val);
    if(err != ESP_OK) {
        log_e("Failed to add attriute to the device");
        return err;
    }
    return ESP_OK;
}

param_handle_t* getParamHandlebyName(esp_rmaker_device_t *device_handle, const char *param_name)
{
    param_handle_t *param = esp_rmaker_device_get_param_by_name(device_handle, param_name);
    return param;
}

void RMakerGenericClass::assignPrimaryParam(const char *param_name)
{
    if(param_name == ESP_RMAKER_DEF_NAME_PARAM && param_handle[NAME_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[NAME_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_POWER_NAME && param_handle[POWER_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[POWER_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_BRIGHTNESS_NAME && param_handle[BRIGHTNESS_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[BRIGHTNESS_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_HUE_NAME && param_handle[HUE_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[HUE_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_SATURATION_NAME && param_handle[SATURATION_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[SATURATION_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_INTENSITY_NAME && param_handle[INTENSITY_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[INTENSITY_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_CCT_NAME && param_handle[CCT_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[CCT_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_DIRECTION_NAME && param_handle[DIRECTION_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[DIRECTION_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_SPEED_NAME && param_handle[SPEED_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[SPEED_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_TEMPERATURE_NAME && param_handle[TEMPERATURE_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[TEMPERATURE_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_STATUS_NAME && param_handle[STATUS_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[STATUS_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_INFO_NAME && param_handle[INFO_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[INFO_PARAM]);
    } else if(param_name == ESP_RMAKER_DEF_OTA_URL_NAME && param_handle[URL_PARAM] != NULL) {
        esp_rmaker_device_assign_primary_param(getDeviceHandle(), param_handle[URL_PARAM]);
    } else {
        log_e("Invalid Parameter");
        return;
    }
}

//Generic Device Parameter
esp_err_t RMakerGenericClass::addParam(Param parameter)
{
    err = esp_rmaker_device_add_param(getDeviceHandle(), parameter.getParamHandle());
    if(err != ESP_OK) {
        log_e("Creating new parameter error");
        return err;
    }
    return ESP_OK;
}

//Standard Device Parameter
esp_err_t RMakerGenericClass::addNameParam(const char *param_name)
{
    param_handle[NAME_PARAM] = esp_rmaker_name_param_create(param_name, getDeviceName());
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[NAME_PARAM]);
}

esp_err_t RMakerGenericClass::addPowerParam(bool val, const char *param_name)
{
    param_handle[POWER_PARAM] = esp_rmaker_power_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[POWER_PARAM]);
}

esp_err_t RMakerGenericClass::addBrightnessParam(int val, const char *param_name)
{
    param_handle[BRIGHTNESS_PARAM] = esp_rmaker_brightness_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[BRIGHTNESS_PARAM]);
}

esp_err_t RMakerGenericClass::addHueParam(int val, const char *param_name)
{
    param_handle[HUE_PARAM] = esp_rmaker_hue_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[HUE_PARAM]);

}

esp_err_t RMakerGenericClass::addSaturationParam(int val, const char *param_name)
{
    param_handle[SATURATION_PARAM] = esp_rmaker_saturation_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[SATURATION_PARAM]);
}

esp_err_t RMakerGenericClass::addIntensityParam(int val, const char *param_name)
{
    param_handle[INTENSITY_PARAM] = esp_rmaker_intensity_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[INTENSITY_PARAM]);
}

esp_err_t RMakerGenericClass::addCctParam(int val, const char *param_name)
{
    param_handle[CCT_PARAM] = esp_rmaker_cct_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[CCT_PARAM]);
}

esp_err_t RMakerGenericClass::addDirectionParam(int val, const char *param_name)
{
    param_handle[DIRECTION_PARAM] = esp_rmaker_direction_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[DIRECTION_PARAM]);
}

esp_err_t RMakerGenericClass::addSpeedParam(int val, const char *param_name)
{
    param_handle[SPEED_PARAM] = esp_rmaker_speed_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[SPEED_PARAM]);
}

esp_err_t RMakerGenericClass::addTempratureParam(float val, const char *param_name)
{
    param_handle[TEMPERATURE_PARAM] = esp_rmaker_temperature_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[TEMPERATURE_PARAM]);

}

//Service parameter
esp_err_t RMakerGenericClass::addOTAStatusParam(const char *param_name)
{
    param_handle[STATUS_PARAM] = esp_rmaker_ota_status_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[STATUS_PARAM]);
}

esp_err_t RMakerGenericClass::addOTAInfoParam(const char *param_name)
{
    param_handle[INFO_PARAM] = esp_rmaker_ota_info_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[INFO_PARAM]);
}

esp_err_t RMakerGenericClass::addOTAUrlParam(const char *param_name)
{
    param_handle[URL_PARAM] = esp_rmaker_ota_url_param_create(param_name);
    return esp_rmaker_device_add_param(getDeviceHandle(), param_handle[URL_PARAM]);
}

esp_err_t RMakerGenericClass::updateAndReportParam(const char *param_name, bool my_val)
{
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_bool(my_val);
    err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter fail");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %s", getDeviceName(), param_name, my_val ? "true" : "false");
    }
    return ESP_OK;
}

esp_err_t RMakerGenericClass::updateAndReportParam(const char *param_name, int my_val)
{  
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_int(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter fail");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %d", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;  
}

esp_err_t RMakerGenericClass::updateAndReportParam(const char *param_name, float my_val)
{  
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_float(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter fail");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %f", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;  
}

esp_err_t RMakerGenericClass::updateAndReportParam(const char *param_name, const char *my_val)
{  
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_str(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter fail");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %s", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;  
}
