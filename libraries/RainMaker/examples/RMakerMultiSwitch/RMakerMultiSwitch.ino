//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
#include "WiFi.h"

static Node devkitc;

static int gpio_0 = 0;
static int gpio_16 = 16;
static int gpio_17 = 17;
bool button_state = true;

static Switch switch1("switch1", &gpio_0);
static Switch switch2("switch2", &gpio_16);
static Switch switch3("switch3", &gpio_17);

void write_callback(Device device, Param param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device.getDeviceName();
    const char *param_name = param.getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        if(strcmp(device_name, "switch1") == 0) {
            button_state = val.val.b;
        }
    }
    if(priv_data != NULL)
      Serial.printf("\nSwitch at pin : %d\n",*(int *)priv_data);
    param.updateAndReport(val);
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    
    WiFi.init();
 
    devkitc = RMaker.initNode("ESP Rainmaker Device", "Multi-Switch");

    switch1.addCb(write_callback, NULL); 
    switch2.addCb(write_callback, NULL);
    switch3.addCb(write_callback, NULL);
    
    devkitc.addDevice(switch1); 
    devkitc.addDevice(switch2);
    devkitc.addDevice(switch3);

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
    if(digitalRead(gpio_0) == LOW) {
        button_state = !button_state;
        switch1.updateAndReportParam("Power", button_state);
    }
    delay(100);
}
