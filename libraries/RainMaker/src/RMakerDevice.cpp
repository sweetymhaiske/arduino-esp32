#include "RMakerDevice.h"

void Device :: createDevice(const char *dev_name, const char *dev_type, void *priv_data)
{
    setDeviceName(dev_name);
    esp_rmaker_device_t *dev_handle = esp_rmaker_device_create(dev_name, dev_type, priv_data);
    setDeviceHandle(dev_handle);
    if(dev_handle == NULL){
        log_e("Device Create Error");
    }
}
