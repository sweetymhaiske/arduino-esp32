#include "RMaker.h"
#include "WiFi.h"
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <driver/gpio.h>
#include <esp_rmaker_user_mapping.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp_rmaker_standard_params.h>
static bool g_power_state = DEFAULT_SWITCH_POWER;
esp_rmaker_node_t *node = NULL;
#undef IPADDR_NONE
extern esp_rmaker_param_t *getParamHandle(const char *param_name);

static EventGroupHandle_t wifi_event_group;
static const int WIFI_CONNECTED_EVENT = BIT0;
//const int button_gpio = 0;
extern bool tcpipInit();
bool rainmaker = false;

static void event_handler(void* arg, esp_event_base_t event_base,
                          int event_id, void* event_data)
{
    if (event_base == RMAKER_EVENT) {
        switch (event_id) {
            case RMAKER_EVENT_INIT_DONE:
                log_i("RainMaker Initialised.");
                break;
            case RMAKER_EVENT_CLAIM_STARTED:
                log_i("RainMaker Claim Started.");
                break;
            case RMAKER_EVENT_CLAIM_SUCCESSFUL:
                log_i("RainMaker Claim Successful.");
                break;
            case RMAKER_EVENT_CLAIM_FAILED:
                log_i("RainMaker Claim Failed.");
                break;
            default:
                log_i("Unhandled RainMaker Event:");
        }
    } else {
        log_i("Invalid event received!");
    }   
}
/*
static void set_power_state(bool target)
{
    gpio_set_level(GPIO_NUM_19, target);
}

int IRAM_ATTR app_driver_set_state(bool state)
{
    if(g_power_state != state) {
        g_power_state = state;
        set_power_state(g_power_state);
    }   
    return ESP_OK;
}

static void push_btn_cb()
{
    bool new_state = !g_power_state;
    app_driver_set_state(new_state);
}
*/
/*void hello()
{
    pinMode(button_gpio, INPUT);
}
//int buttonState = 0;
void app_driver_init()
{
//    pinMode(button_gpio, INPUT);
  //  int buttonState = 0;
    //while(1){
        buttonState = digitalRead(button_gpio);
        if(buttonState == HIGH){
            log_i("HELLO");
        }
        else
        {
            log_i("HI");
        } 
    //}
    gpio_config_t io_conf = {
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE
    };
    io_conf.pin_bit_mask = ((uint64_t)1 << GPIO_NUM_19);
    Configure the GPIO 
    gpio_config(&io_conf);
}*/

esp_rmaker_node_t* RMakerClass::initNode(char *node_name, char *node_type)
{
    //app_driver_init();
    rainmaker = true;
    if(tcpipInit() == false){
        log_e("Init Fail");   
    }
    wifi_event_group = xEventGroupCreate();
    
    esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL);
    
    esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);

    esp_rmaker_config_t rainmaker_cfg;
    rainmaker_cfg.enable_time_sync = false;
 
    node = esp_rmaker_node_init(&rainmaker_cfg, node_name, node_type);
    if (!node){
        log_e("Could not initialise Node.");
        return NULL;
    }
    return node;
}

void RMakerClass::start()
{
    esp_err_t err = esp_rmaker_start();    
    if(err != ESP_OK){
        log_e("ESP RainMaker core task fail");
        return;
    }
    WiFi.beginProvision(); 
}

void RMakerClass::addNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device)
{
    esp_err_t err;
    err = esp_rmaker_node_add_device(node, device.getDeviceHandle());
    if(err != ESP_OK){
        log_e("Device was not added to the Node");
        return;
    }
}
void RMakerClass::removeNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device)
{
    esp_err_t err;
    err = esp_rmaker_node_remove_device(node, device.getDeviceHandle());
    if(err != ESP_OK){
        log_e("Device was not added to the Node");
        return;
    }   
}

esp_err_t RMakerClass::stop()
{
    return esp_rmaker_stop();
}

void RMakerClass::deinitNode(const esp_rmaker_node_t *node)
{
    esp_err_t err = esp_rmaker_node_deinit(node);
    if(err != ESP_OK) {
        log_e("Node deinit fail");
    }
}

const esp_rmaker_node_t *getNode()
{
    return esp_rmaker_get_node();
}
char * RMakerClass::getNodeID()
{
    return esp_rmaker_get_node_id();
}

esp_rmaker_node_info_t* RMakerClass::getNodeInfo()
{
    return esp_rmaker_node_get_info(getNode());
}

esp_err_t RMakerClass::addNodeAttr(const char *attr_name, const char *val)
{
    return esp_rmaker_node_add_attribute(getNode(), attr_name, val);
}

void RMakerClass::updateAndReportParam(const param_handle *param, const param_val val)
{
    esp_err_t err = esp_rmaker_param_update_and_report(param, val);
    if(err != ESP_OK) {
        log_e("Update Parameter error");
    }   
}

char *RMakerClass::getParamName(const param_handle *param)
{
    return (char*)esp_rmaker_param_get_name(param);
}

char *RMakerClass::getDeviceName(const device_handle *device)
{
    return (char *)esp_rmaker_device_get_name(device);
}
RMakerClass RMaker;
