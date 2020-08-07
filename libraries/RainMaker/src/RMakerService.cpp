#include "RMakerService.h"

void Service::createService(const char *serv_name, const char *serv_type, void *priv_data)
{
    setServiceName(serv_name);
    esp_rmaker_device_t *dev_handle = esp_rmaker_service_create(serv_name, serv_type, priv_data);
    setDeviceHandle(dev_handle);
    if(dev_handle == NULL) {
        log_e("Service create error");
    }
}
