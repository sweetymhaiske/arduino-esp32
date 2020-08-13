//This example demonstrate the RainMaker Fan example
#include "RMaker.h"
static node_t my_node;
static Fan my_fan(NULL);
static int g_speed = DEFAULT_FAN_SPEED;

static const int button_gpio = 0;
int buttonState = 0;

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    } else if (strcmp(param_name, "speed") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
        g_speed = val.val.i;
    }  
    RMaker.updateAndReportParam();
}

void setup()
{
    Serial.begin(115200);
    pinMode(button_gpio, INPUT);
    
    my_node = RMaker.initNode("ESP Rainmaker Device", "Fan");

    my_fan.addCb(write_callback, NULL);
    my_fan.addSpeedParam(DEFAULT_FAN_SPEED);
    RMaker.addNodeDevice(my_node, my_fan);

    RMaker.start();
}

void loop()
{
    buttonState = digitalRead(button_gpio);
    if(buttonState == LOW) {
        int old_speed = g_speed;
        g_speed++;
        if(g_speed > 5) {
            g_speed = 0;
        }
        my_fan.updateAndReportParam("speed", g_speed);
        if(old_speed == 0) {
            my_fan.updateAndReportParam("power", true);
        } else if(g_speed == 0) {
            my_fan.updateAndReportParam("power", false);
        }
    }
    delay(100);
}
