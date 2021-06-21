#include "RMakerDevice.h"
//#if ESP_IDF_VERSION_MAJOR >= 4 && CONFIG_ESP_RMAKER_TASK_STACK && CONFIG_IDF_TARGET_ESP32

static esp_err_t err;
typedef void (*deviceWriteCb)(Device*, Param*, const param_val_t val, void *priv_data, write_ctx_t *ctx);
typedef void (*deviceReadCb)(Device*, Param*, void *priv_data, read_ctx_t *ctx);

void (*write_cb)(Device*, Param*, param_val_t, void*, write_ctx_t*);
void (*read_cb)(Device*, Param*, void*, read_ctx_t*);
Device device;
Param param;

static esp_err_t write_callback(const device_handle_t *dev_handle, const param_handle_t *par_handle, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    device.setDeviceHandle(dev_handle);
    param.setParamHandle(par_handle);

    write_cb(&device, &param, val, priv_data, ctx);
    return ESP_OK;
}

static esp_err_t read_callback(const device_handle_t *dev_handle, const param_handle_t *par_handle, void *priv_data, read_ctx_t *ctx)
{
    device.setDeviceHandle(dev_handle);
    param.setParamHandle(par_handle);

    read_cb(&device, &param, priv_data, ctx);
    return ESP_OK;
}

esp_err_t Device::deleteDevice()
{
    err = esp_rmaker_device_delete(getDeviceHandle());
    if(err != ESP_OK) {
        log_e("Device deletion error");
        return err;
    }   
    return ESP_OK;
}

void Device::addCb(deviceWriteCb writeCb, deviceReadCb readCb)
{
    write_cb = writeCb;
    read_cb = readCb;
    err = esp_rmaker_device_add_cb(getDeviceHandle(), write_callback, read_callback);
    if(err != ESP_OK) {
        log_e("Callback register error");
    }   
}

esp_err_t Device::addDeviceAttr(const char *attr_name, const char *val)
{
    err = esp_rmaker_device_add_attribute(getDeviceHandle(), attr_name, val);
    if(err != ESP_OK) {
        log_e("Failed to add attriute to the device");
        return err;
    }
    return ESP_OK;
}

//Generic Parameter
esp_err_t Device::addParam(Param parameter)
{
    err = esp_rmaker_device_add_param(getDeviceHandle(), parameter.getParamHandle());
    if(err != ESP_OK) {
        log_e("Adding custom parameter error");
        return err;
    }
    return ESP_OK;
}

//Standard Device Parameter
esp_err_t Device::addNameParam(const char *param_name)
{
    param_handle_t *param = esp_rmaker_name_param_create(param_name, getDeviceName());
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addPowerParam(bool val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_power_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addBrightnessParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_brightness_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addHueParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_hue_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addSaturationParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_saturation_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addIntensityParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_intensity_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addCCTParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_cct_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addDirectionParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_direction_param_create(param_name, val); 
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addSpeedParam(int val, const char *param_name)
{
    param_handle_t *param = esp_rmaker_speed_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

esp_err_t Device::addTempratureParam(float val, const char *param_name)
{   
    param_handle_t *param = esp_rmaker_temperature_param_create(param_name, val);
    return esp_rmaker_device_add_param(getDeviceHandle(), param);
}

param_handle_t *Device::getParamByName(const char *param_name)
{
    return esp_rmaker_device_get_param_by_name(getDeviceHandle(), param_name);
}

esp_err_t Device::assignPrimaryParam(param_handle_t *param)
{
    err = esp_rmaker_device_assign_primary_param(getDeviceHandle(), param);
    if(err != ESP_OK){
        log_e("Assigning primary param error");
    }
    return err;
}

const param_handle_t* getParamHandlebyName(const esp_rmaker_device_t *device_handle, const char *param_name)
{
    const param_handle_t *param = esp_rmaker_device_get_param_by_name(device_handle, param_name);
    return param;
}

esp_err_t Device::updateAndReportParam(const char *param_name, bool my_val)
{
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_bool(my_val);
    err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter failed");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %s", getDeviceName(), param_name, my_val ? "true" : "false");
    }
    return ESP_OK;
}

esp_err_t Device::updateAndReportParam(const char *param_name, int my_val)
{
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_int(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter failed");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %d", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;
}

esp_err_t Device::updateAndReportParam(const char *param_name, float my_val)
{
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_float(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter failed");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %f", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;
}

esp_err_t Device::updateAndReportParam(const char *param_name, const char *my_val)
{
    const param_handle_t *param = getParamHandlebyName(getDeviceHandle(), param_name);
    param_val_t val = esp_rmaker_str(my_val);
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update paramter failed");
        return err;
    }else {
        log_i("Device : %s, Param Name : %s, Val : %s", getDeviceName(), param_name, my_val);
    }
    return ESP_OK;
}

//#endif
