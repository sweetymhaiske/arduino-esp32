#include "RMaker.h"
#include "WiFi.h"
#include <esp_wifi.h>
#include <nvs_flash.h>
#include <esp_rmaker_user_mapping.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>

#undef IPADDR_NONE

static EventGroupHandle_t wifi_event_group;
static const int WIFI_CONNECTED_EVENT = BIT0;
const int button_gpio = 0;
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
void app_driver_init()
{
   pinMode(button_gpio, INPUT);
}

void RMakerClass::init(char *node_name, char *node_type)
{
    rainmaker = true;
    esp_rmaker_console_init();
    app_driver_init();
    esp_err_t err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        nvs_flash_erase();
        log_i("NVS ERROR");
        err = nvs_flash_init();
    }
    if(tcpipInit() == false){
        log_e("Init Fail");   
    }
    wifi_event_group = xEventGroupCreate();
    
    esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL);
    
    esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);

    esp_rmaker_config_t rainmaker_cfg;
    rainmaker_cfg.info.name = node_name;
    rainmaker_cfg.info.type = node_type;
    rainmaker_cfg.info.fw_version = NULL;
    rainmaker_cfg.info.model = NULL;
    rainmaker_cfg.enable_time_sync = false;
 
    err = esp_rmaker_init(&rainmaker_cfg);
    if (err != ESP_OK) {
        log_e("Could not initialise ESP RainMaker. Aborting!!!");
    }
    if(err == ESP_OK)
        log_i("Rainmaker Initialised successfully\n");   
}

void RMakerClass::start()
{
    esp_err_t err = esp_rmaker_start();    
    if(err != ESP_OK){
        log_e("ESP RainMaker core task fail");
        return;
    }
    WiFi.beginProvision(); 
    xEventGroupWaitBits(wifi_event_group, WIFI_CONNECTED_EVENT, false, true, portMAX_DELAY);
}

esp_err_t RMakerClass::stop()
{
    return esp_rmaker_stop();
}

char * RMakerClass::getNodeID()
{
    return esp_rmaker_get_node_id();
}

esp_rmaker_node_info_t* RMakerClass::getNodeInfo()
{
    return esp_rmaker_get_node_info();
}

esp_err_t RMakerClass::addNodeAttr(const char *attr_name, const char *val)
{
    return esp_rmaker_node_add_attribute(attr_name, val);
}

RMakerClass RMaker;
