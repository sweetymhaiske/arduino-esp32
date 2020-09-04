//This example demonstrate the Rainmaker Switch example
#include "RMaker.h"
static Node devkitc;

static int gpio_0 = 0;
static int gpio_16 = 16;
static int gpio_17 = 17;
bool buttonState = true;

static Switch switch1("switch1", &gpio_0);
static Switch switch2("switch2", &gpio_16);
static Switch switch3("switch3", &gpio_17);

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
        if(strcmp(device_name, "switch1") == 0) {
            buttonState = val.val.b;
        }
    }
    if(priv_data != NULL)
      Serial.printf("\nSwitch at pin : %d",*(int *)priv_data);
    RMaker.updateAndReportParam();
}

void setup()
{
    Serial.begin(115200);
    pinMode(gpio_0, INPUT);
 
    devkitc = RMaker.initNode("ESP Rainmaker Device", "Multi-Switch");

    switch1.addCb(write_callback, NULL); 
    switch2.addCb(write_callback, NULL);
    switch3.addCb(write_callback, NULL);
    
    devkitc.addDevice(switch1); 
    devkitc.addDevice(switch2);
    devkitc.addDevice(switch3);
  
    RMaker.start();
}

void loop()
{
    if(digitalRead(gpio_0) == LOW) {
        buttonState = !buttonState;
        switch1.updateAndReportParam("power", buttonState);
    }
    delay(100);
}
