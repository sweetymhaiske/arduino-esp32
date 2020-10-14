#include "RMakerType.h"
#include "RMakerParam.h"
#include <esp_rmaker_standard_devices.h>
#include <esp_rmaker_standard_params.h>
#include <esp32-hal.h>
#include <map>

class Device
{
    private:
        const char *device_name;
        const device_handle_t *device_handle;
        std::map<const char *, const param_handle_t *> mp;

    public:
        Device()
        {
            device_name = NULL;
            device_handle = NULL;
        }        
        //setter methods
        void setDeviceName(const char *device_name)
        {
            this->device_name = device_name;
        }
        void setDeviceHandle(const esp_rmaker_device_t *device_handle)
        {
            this->device_handle = device_handle;
        }

        //getter methods
        const char *getDeviceName()
        {
            return device_name;
        }
        const char *getServiceName()
        {   
            return device_name;
        }
        const esp_rmaker_device_t *getDeviceHandle()
        {
            return device_handle;
        }
        
        typedef void (*deviceWriteCb)(Device, Param, const param_val_t val, void *priv_data, write_ctx_t *ctx);
        typedef void (*deviceReadCb)(Device, Param, void *priv_data, read_ctx_t *ctx);

        esp_err_t deleteDevice();
        void addCb(deviceWriteCb write_cb, deviceReadCb read_cb);
        esp_err_t addDeviceAttr(const char *attr_name, const char *val);
        void assignPrimaryParam(const char *param_name);
        
        //Generic Device Parameter
        esp_err_t addParam(Param parameter);

        //Standard Device Parameter
        esp_err_t addNameParam(const char *param_name = ESP_RMAKER_DEF_NAME_PARAM);
        esp_err_t addPowerParam(bool val, const char *param_name = ESP_RMAKER_DEF_POWER_NAME);
        esp_err_t addBrightnessParam(int val, const char *param_name = ESP_RMAKER_DEF_BRIGHTNESS_NAME);
        esp_err_t addHueParam(int val, const char *param_name = ESP_RMAKER_DEF_HUE_NAME);
        esp_err_t addSaturationParam(int val, const char *param_name = ESP_RMAKER_DEF_SATURATION_NAME);
        esp_err_t addIntensityParam(int val, const char *param_name = ESP_RMAKER_DEF_INTENSITY_NAME);
        esp_err_t addCctParam(int val, const char *param_name = ESP_RMAKER_DEF_CCT_NAME);
        esp_err_t addDirectionParam(int val, const char *param_name = ESP_RMAKER_DEF_DIRECTION_NAME);
        esp_err_t addSpeedParam(int val, const char *param_name = ESP_RMAKER_DEF_SPEED_NAME);
        esp_err_t addTempratureParam(float val, const char *param_name = ESP_RMAKER_DEF_TEMPERATURE_NAME);
          
        //Update Paramters
        esp_err_t updateAndReportParam(const char *param_name, bool val);
        esp_err_t updateAndReportParam(const char *param_name, int  val);
        esp_err_t updateAndReportParam(const char *param_name, float val);
        esp_err_t updateAndReportParam(const char *param_name, const char *val);

};

static Device createDevice(const char *dev_name, const char *dev_type, void *priv_data)
{
    Device new_device;
    new_device.setDeviceName(dev_name);
    esp_rmaker_device_t *dev_handle = esp_rmaker_device_create(dev_name, dev_type, priv_data);
    new_device.setDeviceHandle(dev_handle);
    if(dev_handle == NULL){
        log_e("Device create error");
    }   
    return new_device;
}

static Device createService(const char *serv_name, const char *serv_type, void *priv_data)
{
    Device new_service;
    new_service.setDeviceName(serv_name);
    esp_rmaker_device_t *dev_handle = esp_rmaker_device_create(serv_name, serv_type, priv_data);
    new_service.setDeviceHandle(dev_handle);
    if(dev_handle == NULL){
        log_e("Device create error");
    }   
    return new_service;
}

class Switch : public Device
{
    public:
        Switch()
        {
            standardSwitchDevice("Switch", NULL, DEFAULT_SWITCH_POWER);
        }
        Switch(const char *dev_name, void *priv_data = NULL, bool power = DEFAULT_SWITCH_POWER)
        {
            standardSwitchDevice(dev_name, priv_data, power);
        }
        void standardSwitchDevice(const char *dev_name, void *priv_data, bool power)
        {
            setDeviceName(dev_name);
            esp_rmaker_device_t *dev_handle = esp_rmaker_switch_device_create(dev_name, priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Switch device not created");
            }   
        } 
};

class LightBulb : public Device
{
    public:
        LightBulb()
        {
            standardLightBulbDevice("Light", NULL, DEFAULT_LIGHT_POWER);
        }
        LightBulb(const char *dev_name, void *priv_data = NULL, bool power = DEFAULT_LIGHT_POWER)
        {
            standardLightBulbDevice(dev_name, priv_data, power);
        }
        void standardLightBulbDevice(const char *dev_name, void *priv_data, bool power)
        {
            setDeviceName(dev_name);
            esp_rmaker_device_t *dev_handle = esp_rmaker_lightbulb_device_create(dev_name, priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Light device not created");
            }   
        }  
};       

class Fan : public Device
{
    public:
        Fan()
        {
            standardFanDevice("Fan", NULL, DEFAULT_FAN_POWER);
        }
        Fan(const char *dev_name, void *priv_data = NULL, bool power = DEFAULT_FAN_POWER)
        {
            standardFanDevice(dev_name, priv_data, power);
        }
        void standardFanDevice(const char *dev_name, void *priv_data, bool power)
        {
            setDeviceName(dev_name);
            esp_rmaker_device_t *dev_handle = esp_rmaker_fan_device_create(dev_name, priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Fan device not created");
            }
        } 
};

class TemperatureSensor : public Device
{
    public:
        TemperatureSensor()
        {
            standardTemperatureSensorDevice("Temperature-Sensor", NULL, DEFAULT_TEMPERATURE);
        }
        TemperatureSensor(const char *dev_name, void *priv_data = NULL, float temp = DEFAULT_TEMPERATURE)
        {
            standardTemperatureSensorDevice(dev_name, priv_data, temp);
        }
        void standardTemperatureSensorDevice(const char *dev_name, void *priv_data, float temp)
        {
            setDeviceName(dev_name);
            esp_rmaker_device_t *dev_handle = esp_rmaker_temp_sensor_device_create(dev_name, priv_data, temp);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Temperature Sensor device not created");
            }
        }
};
