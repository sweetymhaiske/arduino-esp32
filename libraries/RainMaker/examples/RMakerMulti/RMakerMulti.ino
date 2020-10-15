#include "RMaker.h"
#include "WiFi.h"

static Node my_node;
static Switch switch_device;
static LightBulb light_device;
static TemperatureSensor temp_sensor_device;

static const int button_gpio = 0;
int button_state = 0;

void write_callback(Device device, Param param, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    const char *device_name = device.getDeviceName();
    const char *param_name = param.getParamName();

    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s\n", val.val.b? "true" : "false", device_name, param_name);
    } else if(strcmp(param_name, "Brightness") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s\n", val.val.i, device_name, param_name);
    } 
    param.updateAndReport(val);
}

void setup()
{
    Serial.begin(115200);
    pinMode(button_gpio, INPUT);
    
    WiFi.init();
    
    my_node = RMaker.initNode("ESP Rainmaker Multi Device", "Multi Device");

    switch_device.addCb(write_callback, NULL); 
    my_node.addDevice(switch_device);
    
    light_device.addCb(write_callback, NULL);
    light_device.addBrightnessParam(DEFAULT_LIGHT_BRIGHTNESS);
    light_device.addDeviceAttr("serial_number", "012345");
    light_device.addDeviceAttr("mac", "xx:yy:zz:aa:bb:cc");
    my_node.addDevice(light_device);

    my_node.addDevice(temp_sensor_device);
    
    RMaker.start();

#if CONFIG_IDF_TARGET_ESP32
    WiFi.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#else
    WiFi.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#endif

}

void loop()
{
    button_state = digitalRead(button_gpio);
    if(button_state == LOW) {
        light_device.updateAndReportParam("Brightness", DEFAULT_LIGHT_BRIGHTNESS);
    }
    delay(100);
}
