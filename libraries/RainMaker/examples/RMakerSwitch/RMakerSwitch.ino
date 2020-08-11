//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
static node_t my_node;
static Device my_device;

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    }
}

void setup()
{
    Serial.begin(115200);
     
    my_node = RMaker.initNode("ESP Rainmaker Device", "Switch");

    my_device.createDevice("Switch", ESP_RMAKER_DEVICE_SWITCH, NULL);
    my_device.addCb(write_callback, NULL); 
    my_device.addNameParam();
    my_device.addPowerParam(true);
    my_device.assignPrimaryParam("power");
    RMaker.addNodeDevice(my_node, my_device);
    
    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.start();
}

void loop()
{

}
