#include <esp_err.h>
#include "RMakerType.h"

typedef esp_err_t (*DeviceParamCb)(const char *dev_name, const char *param_name, Param_t val, void *data);

class RMakerGenericClass
{
    public:
        //Provide Information of the Node its Name and Type
        void rmakerInit(char *node_name, char *node_type);
        
        //esp_rmaker_core.h
        esp_err_t createDevice(const char *dev_name, const char *dev_type, DeviceParamCb cb, void *data);
        esp_err_t deviceAssignPrimaryParam(const char *dev_name, const char *param_name);

        //Add parameter to the device [ esp_rmaker_standard_params.h ]
        esp_err_t deviceAddNameParam(const char *dev_name, const char *param_name);
        esp_err_t deviceAddPowerParam(const char *dev_name, const char *param_name, bool val);
        esp_err_t deviceAddBrightnessParam(const char *dev_name, const char *param_name, int val);        
        esp_err_t deviceAddHueParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddSaturationParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddIntensityParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddCctParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddDirectionParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddSpeedParam(const char *dev_name, const char *param_name, int val);
        esp_err_t deviceAddTempratureParam(const char *dev_name, const char *param_name, float val);
        
        //Add parameter to the service
        esp_err_t serviceAddOTAStatusParam(const char *serv_name, const char *param_name);
        esp_err_t serviceAddOTAInfoParam(const char *serv_name, const char *param_name);
        esp_err_t serviceAddOTAUrlParam(const char *serv_name, const char *param_name);

        //UPdate parameter
        esp_err_t updateParam(const char *dev_name, const char *param_name, Param_t val);
};
