#include "RMaker.h"
static Node my_node;
static Switch switch_device;
static LightBulb light_device;
static TemperatureSensor temp_sensor_device;

static const int button_gpio = 0;
int buttonState = 0;

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    } else if(strcmp(param_name, "brightness") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
    } 
    RMaker.updateAndReportParam();
}

void setup()
{
    Serial.begin(115200);
    pinMode(button_gpio, INPUT);
    
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
}

void loop()
{
    buttonState = digitalRead(button_gpio);
    if(buttonState == LOW) {
        light_device.updateAndReportParam("brightness", DEFAULT_LIGHT_BRIGHTNESS);
    }
    delay(100);
}
