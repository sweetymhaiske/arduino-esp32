//This example demonstrate the RainMaker Fan example
#include "RMaker.h"
#include "WiFi.h"

static Node my_node;
static Fan my_fan;
static int g_speed = DEFAULT_FAN_SPEED;

static const int button_gpio = 0;
int buttonState = 0;

void write_callback(const char *device_name, const char *param_name, const param_val_t val, void *priv_data, write_ctx_t *ctx)
{
    if(strcmp(param_name, "Power") == 0) {
        Serial.printf("\nReceived value = %s for %s - %s", val.val.b? "true" : "false", device_name, param_name);
    } else if (strcmp(param_name, "Speed") == 0) {
        Serial.printf("\nReceived value = %d for %s - %s", val.val.i, device_name, param_name);
        g_speed = val.val.i;
    }  
    RMaker.updateAndReportParam();
}

void setup()
{
    Serial.begin(115200);
    pinMode(button_gpio, INPUT);
    
    WiFi.init();
    
    my_node = RMaker.initNode("ESP Rainmaker Device", "Fan");

    my_fan.addCb(write_callback, NULL);
    my_fan.addSpeedParam(DEFAULT_FAN_SPEED);
    my_node.addDevice(my_fan);

    RMaker.start();

#if CONFIG_IDF_TARGET_ESP32
    WiFi.beginProvision(WIFI_PROV_SCHEME_BLE, WIFI_PROV_SCHEME_HANDLER_FREE_BTDM, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#else
    WiFi.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_1234");
#endif

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
        my_fan.updateAndReportParam("Speed", g_speed);
        if(old_speed == 0) {
            my_fan.updateAndReportParam("Power", true);
        } else if(g_speed == 0) {
            my_fan.updateAndReportParam("Power", false);
        }
    }
    delay(100);
}
