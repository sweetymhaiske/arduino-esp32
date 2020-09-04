#include "RMakerGeneric.h"
#include <esp_rmaker_standard_services.h>
#include <esp32-hal.h>

class Service : public RMakerGenericClass
{
    public:
        void createService(const char *serv_name, const char *serv_type, void *priv_data);
};

class OTAService : public RMakerGenericClass
{
    public:
        OTAService()
        {
            standardOTAService("ota", NULL);
        }
        OTAService(const char *ota_name, void *priv_data)
        {
            standardOTAService(ota_name, priv_data);
        }
        void standardOTAService(const char *ota_name, void *priv_data)
        {
            setServiceName(ota_name);
            esp_rmaker_device_t *dev_handle = esp_rmaker_ota_service_create(ota_name, priv_data);
            setDeviceHandle(dev_handle);
            if(dev_handle == NULL){
                log_e("OTA Service not created");
            }
        }
};
