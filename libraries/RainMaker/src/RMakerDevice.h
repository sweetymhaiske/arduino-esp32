#include "RMakerGeneric.h"
#include "RMakerType.h"
#include <esp_rmaker_standard_devices.h>
#include <esp32-hal.h>

class Device : public RMakerGenericClass
{
    public:
        void createDevice(const char *dev_name, const char *dev_type, void *priv_data);
};

class Switch : public RMakerGenericClass
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

class LightBulb : public RMakerGenericClass
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

class Fan : public RMakerGenericClass
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

class TemperatureSensor : public RMakerGenericClass
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
