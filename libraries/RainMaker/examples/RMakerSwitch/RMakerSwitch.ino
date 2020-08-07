//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
#include "WiFi.h"
static Node my_node;
static Device my_device;
static LightBulb my_light(NULL);

static esp_err_t device_write_callback(const device_handle *device, const param_handle *param, const param_val val, void *priv_data, write_ctx *ctx)
{
    char *param_name = RMaker.getParamName(param);
    char *device_name = RMaker.getDeviceName(device);
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s",val.val.b? "true" : "false", device_name, param_name);
    }
    RMaker.updateAndReportParam(param, val);
    return ESP_OK;
}

static esp_err_t light_write_callback(const device_handle *device, const param_handle *param, const param_val val, void *priv_data, write_ctx *ctx)
{
    char *param_name = RMaker.getParamName(param);
    char *device_name = RMaker.getDeviceName(device);
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    } else if (strcmp(param_name, "brightness") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
    } else if (strcmp(param_name, "hue") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
    } else {
        return ESP_OK;
    }   
    RMaker.updateAndReportParam(param, val);
    return ESP_OK;
}

void setup()
{
    Serial.begin(115200);
    my_node = RMaker.initNode("ESP Rainmaker Node", "Switch + Fan + Lightbulb");

    my_device.createDevice("Switch", ESP_RMAKER_DEVICE_SWITCH, NULL);
    my_device.addCb(device_write_callback, NULL); 
    my_device.addNameParam();
    my_device.addPowerParam(true);
    my_device.assignPrimaryParam("power");
    RMaker.addNodeDevice(my_node, my_device);
    
    my_light.addCb(light_write_callback, NULL);
    my_light.addBrightnessParam(25);
    my_light.addHueParam(180);
    my_light.addSaturationParam(100);
    RMaker.addNodeDevice(my_node, my_light);

    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.start();
}

void loop()
{
}
