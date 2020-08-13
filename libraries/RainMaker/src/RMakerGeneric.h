#include <esp_err.h>
#include <esp_rmaker_standard_params.h>
#include "RMakerType.h"
#include "RMakerParam.h"
#define PARAMS 13

class RMakerGenericClass
{
    private:
        const char *device_name;
        const char *service_name;
        esp_rmaker_device_t *device_handle;
        esp_rmaker_param_t *param_handle[PARAMS] = {NULL};
     
    public:
        RMakerGenericClass()
        {
            device_name = NULL;
            service_name = NULL;
            device_handle = NULL;
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
         
        //getter methods
        const char* getDeviceName()
        {
            return device_name;
        }
        
        const char* getServiceName()
        {
            return service_name;
        }
        
        esp_rmaker_device_t* getDeviceHandle()
        {
            return device_handle;
        }
       
        void deleteDevice();
        void addCb(deviceWriteCb write_cb, deviceReadCb read_cb); 
        esp_err_t addDeviceAttr(const char *attr_name, const char *val);
        void assignPrimaryParam(char *param_name);
        
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
        
        //Service Parameter
        esp_err_t addOTAStatusParam(const char *param_name = ESP_RMAKER_DEF_OTA_STATUS_NAME);
        esp_err_t addOTAInfoParam(const char *param_name = ESP_RMAKER_DEF_OTA_INFO_NAME);
        esp_err_t addOTAUrlParam(const char *param_name = ESP_RMAKER_DEF_OTA_URL_NAME);
        
        esp_err_t updateAndReportParam(const char *param_name, bool val);
        esp_err_t updateAndReportParam(const char *param_name, int  val);
        esp_err_t updateAndReportParam(const char *param_name, float val);
        esp_err_t updateAndReportParam(const char *param_name, const char *val);
};
