#include <esp_err.h>
#include "RMakerType.h"
#include <esp_rmaker_standard_params.h>

class RMakerGenericClass
{
    private:
        const char *device_name;
        const char *service_name;
        esp_rmaker_device_t *device_handle;
        esp_rmaker_param_t *param;
    
    public:

        RMakerGenericClass()
        {
            device_name = NULL;
            service_name = NULL;
            device_handle = NULL;
            param =  NULL;
        }

        //setter methods
        void setDeviceName(const char *device_name)
        {
            this->device_name = device_name;
        }
        
        void setServiceName(const char *service_name)
        {
            this->service_name = service_name;
        }        

        void setDeviceHandle(esp_rmaker_device_t *device_handle)
        {
            this->device_handle = device_handle;
        }
        
        void setDeviceParam(esp_rmaker_param_t *param)
        {
            this->param = param;
        }
        
        //getter methods
        const char *getDeviceName()
        {
            return device_name;
        }
        
        const char *getServiceName()
        {
            return service_name;
        }
        
        esp_rmaker_device_t *getDeviceHandle()
        {
            return device_handle;
        }
         
        esp_rmaker_param_t *getDeviceParam()
        {
            return param;
        }

        void addCb(deviceWriteCb write_cb, deviceReadCb read_cb); 
        void deleteDevice();
        esp_err_t addDeviceAttr(const char *attr_name, const char *val);
        void assignPrimaryParam(char *param_name);
        
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
        esp_err_t addOTAStatusParam(const char *param_name = ESP_RMAKER_DEF_OTA_STATUS_NAME);
        esp_err_t addOTAInfoParam(const char *param_name = ESP_RMAKER_DEF_OTA_INFO_NAME);
        esp_err_t addOTAUrlParam(const char *param_name = ESP_RMAKER_DEF_OTA_URL_NAME);
};
