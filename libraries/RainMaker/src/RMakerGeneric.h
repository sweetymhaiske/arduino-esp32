#include <esp_err.h>
#include "RMakerType.h"

typedef esp_err_t (*DeviceParamCb)(const char *dev_name, const char *param_name, Param_t val, void *data);

class RMakerGenericClass
{
    public:
        const char *device_name;

        //Device API
        esp_err_t createDevice(const char *dev_name, const char *dev_type, DeviceParamCb cb, void *priv_data);
        esp_err_t addDeviceAttr(const char *attr_name, const char *val);
        esp_err_t addDeviceParam(const char *param_name, esp_rmaker_param_val_t val, uint8_t properties);
        esp_err_t assignPrimaryParam(const char *param_name);

        //Service API
        esp_err_t createService(const char *serv_name, const char *type, DeviceParamCb cb, void *priv_data);
        esp_err_t addServiceParam(const char *serv_name, const char *param_name, esp_rmaker_param_val_t val, uint8_t properties);

        //Device Parameter
        esp_err_t addNameParam(const char *param_name = "name");
        esp_err_t addPowerParam(bool val, const char *param_name = "power");
        esp_err_t addBrightnessParam(int val, const char *param_name = "brightness");        
        esp_err_t addHueParam(int val, const char *param_name = "hue");
        esp_err_t addSaturationParam(int val, const char *param_name = "saturation");
        esp_err_t addIntensityParam(int val, const char *param_name = "intensity");
        esp_err_t addCctParam(int val, const char *param_name = "cct");
        esp_err_t addDirectionParam(int val, const char *param_name = "direction");
        esp_err_t addSpeedParam(int val, const char *param_name = "speed");
        esp_err_t addTempratureParam(float val, const char *param_name = "temprature");
        
        //Service Parameter
        esp_err_t addOTAStatusParam(const char *serv_name, const char *param_name);
        esp_err_t addOTAInfoParam(const char *serv_name, const char *param_name);
        esp_err_t addOTAUrlParam(const char *serv_name, const char *param_name);

        //Parameter
        esp_err_t updateParam(const char *param_name, Param_t val);
        esp_err_t paramAddUIType(const char *name, const char *ui_type);
        esp_err_t paramAddBounds(const char *param_name, esp_rmaker_param_val_t min, esp_rmaker_param_val_t max, esp_rmaker_param_val_t step);
        esp_err_t paramAddType(const char *param_name, const char* type);
};
