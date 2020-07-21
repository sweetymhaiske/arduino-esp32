//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
#include "WiFi.h"

static esp_err_t light_callback(const char *dev_name, const char *param_name, Param_t val, void *priv_data)
{
    return ESP_OK;
}

static esp_err_t device_callback(const char *dev_name, const char *param_name, Param_t val, void *priv_data)
{
    return ESP_OK;
}

void setup()
{
    Serial.begin(115200);

    WiFi.begin();

    RMaker.init("ESP Rainmaker Device", "Switch + Lightbulb");

    Device my_device;
    my_device.createDevice("Switch", ESP_RMAKER_DEVICE_SWITCH, device_callback, NULL);
    my_device.addNameParam();
    my_device.addPowerParam(true);
    my_device.assignPrimaryParam("power");
    
    LightBulb my_light("Light", light_callback, NULL);
    my_light.addBrightnessParam(25);
    my_light.addHueParam(180);
    my_light.addSaturationParam(100);

    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.start();
    
    WiFi.beginProvision();
}

void loop()
{
}
