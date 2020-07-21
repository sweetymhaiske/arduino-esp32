#include "RMakerGeneric.h"
#include "RMakerType.h"

#include <esp_rmaker_standard_devices.h>

class Device : public RMakerGenericClass
{

};

class Switch : public RMakerGenericClass
{
    public:
        Switch();
        Switch(const char *dev_name, DeviceParamCb cb, void *priv_data)
        {
            device_name = dev_name;
            esp_rmaker_create_switch_device(dev_name, cb, priv_data, DEFAULT_SWITCH_POWER);
        }
};

class LightBulb : public RMakerGenericClass
{
    public:
        LightBulb();
        LightBulb(const char *dev_name, DeviceParamCb cb, void *priv_data)
        {
            device_name = dev_name;
            esp_rmaker_create_lightbulb_device(dev_name, cb, priv_data, DEFAULT_LIGHT_POWER);
        }
};       

class Fan : public RMakerGenericClass
{
    public:
        Fan();
        Fan(const char *dev_name, DeviceParamCb cb, void *priv_data)
        {
            device_name = dev_name;
            esp_rmaker_create_switch_device(dev_name, cb, priv_data, DEFAULT_FAN_POWER);
        }
};


