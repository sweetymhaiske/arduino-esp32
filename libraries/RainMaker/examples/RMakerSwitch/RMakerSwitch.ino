//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
#include "WiFi.h"

static Node my_node;
static Device my_device;

void write_callback(Device device, Param param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device.getDeviceName();
    const char *param_name = param.getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
    }
    param.updateAndReport(val);
}

void setup()
{
    Serial.begin(115200);
    
    WiFi.init();
     
    my_node = RMaker.initNode("ESP Rainmaker Device", "Switch");

    my_device = createDevice("Switch", ESP_RMAKER_DEVICE_SWITCH, NULL);
    my_device.addCb(write_callback, NULL); 
    my_device.addNameParam();
    my_device.addPowerParam(true);
    my_device.assignPrimaryParam("Power");
    my_node.addDevice(my_device);
    
    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.enableSchedule();

    RMaker.start();

#if CONFIG_IDF_TARGET_ESP32
    WiFi.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#else
    WiFi.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#endif

}

void loop()
{

}
