//This example demonstrates the ESP RainMaker with the custom device and standard Fan device.
#include "RMaker.h"
#include "WiFi.h"

#define FAN_SPEED 4
static Node my_node;
static Device my_device("My_Switch");
static Fan my_fan;

const char *service_name = "Prov_1234";
const char *pop = "abcd1234";

static bool button_state = true;
static int gpio_0 = 0;

void sysProvEvent(arduino_event_t *sys_event)
{
    switch (sys_event->event_id) {      
        case ARDUINO_EVENT_PROV_START:
#if CONFIG_IDF_TARGET_ESP32
        printQR(service_name, pop,"ble");
#else
        printQR(service_name, pop,"softap");
#endif        
        break;
    }
}

void write_callback(Device device, Param param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device.getDeviceName();
    const char *param_name = param.getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
        button_state = val.val.b;
    }
    if(strcmp(param_name, "Speed") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s\n", val.val.i, device_name, param_name);
    }
    param.updateAndReport(val);
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
    
    WiFi.init();
     
    my_node = RMaker.initNode("ESP Rainmaker Device", "Switch");
    
    my_device.addNameParam();
    my_device.addPowerParam(true, "Power");
    my_device.assignPrimaryParam(my_device.getParamByName("Power" ));
    my_device.addCb(write_callback, NULL);

    my_fan.addSpeedParam(FAN_SPEED);
    my_fan.addCb(write_callback, NULL);
   
    my_node.addDevice(my_device);
    my_node.addDevice(my_fan);
    
    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.enableSchedule();

    RMaker.start();

    WiFi.onEvent(sysProvEvent);
#if CONFIG_IDF_TARGET_ESP32
    WiFi.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, pop, service_name);
#else
    WiFi.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, pop, service_name);
#endif

}

void loop()
{
    if(digitalRead(gpio_0) == LOW) {
        button_state = !button_state;
        my_device.updateAndReportParam("Power", button_state);
    }
    delay(100);
}
