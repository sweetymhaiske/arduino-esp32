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
        Switch();
        Switch(void *priv_data, bool power = DEFAULT_SWITCH_POWER)
        {
            setDeviceName("Switch");
            esp_rmaker_device_t *dev_handle = esp_rmaker_switch_device_create("Switch", priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Switch device not created");
            }
        }
};

class LightBulb : public RMakerGenericClass
{
    public:
        LightBulb();
        LightBulb(void *priv_data, bool power = DEFAULT_LIGHT_POWER)
        {
            setDeviceName("Light");
            esp_rmaker_device_t *dev_handle = esp_rmaker_lightbulb_device_create("Light", priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Light device not created");
            }
        }   
};       

class Fan : public RMakerGenericClass
{
    public:
        Fan();
        Fan(void *priv_data, bool power = DEFAULT_FAN_POWER)
        {
            setDeviceName("Fan");
            esp_rmaker_device_t *dev_handle = esp_rmaker_fan_device_create("Fan", priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Fan device not created");
            }
        }
};

class TemperatureSensor : public RMakerGenericClass
{
    public:
        TemperatureSensor();
        TemperatureSensor(void *priv_data, bool power = DEFAULT_TEMPERATURE)
        {
            setDeviceName("Temperature Sensor");
            esp_rmaker_device_t *dev_handle = esp_rmaker_temp_sensor_device_create("Temperature Sensor", priv_data, power);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("Temperature Sensor device not created");
            }
        }
};
