//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
static node_t my_node;
static Device my_device;
static LightBulb my_light(NULL);

static const int button_gpio = 0;
int buttonState = 0;

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    } else if (strcmp(param_name, "brightness") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
    } else if (strcmp(param_name, "hue") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
    } else {
        Serial.println("Invalid parameter");
    }   
}

void setup()
{
    Serial.begin(115200);
    pinMode(button_gpio, INPUT);
    
    my_node = RMaker.initNode("ESP Rainmaker Node", "Switch + Lightbulb");

    my_device.createDevice("Switch", ESP_RMAKER_DEVICE_SWITCH, NULL);
    my_device.addCb(write_callback, NULL); 
    my_device.addNameParam();
    my_device.addPowerParam(true);
    my_device.assignPrimaryParam("power");
    RMaker.addNodeDevice(my_node, my_device);
    
    my_light.addCb(write_callback, NULL);
    my_light.addBrightnessParam(25);
    my_light.addHueParam(180);
    my_light.addSaturationParam(100);
    RMaker.addNodeDevice(my_node, my_light);

    RMaker.enableOTA(OTA_USING_PARAMS);
    RMaker.start();
}

void loop()
{
    buttonState = digitalRead(button_gpio);
    if(buttonState == LOW) {
        my_device.updateAndReportParam("power", true);
        my_light.updateAndReportParam("brightness", 80);
    }
    delay(100);
}
