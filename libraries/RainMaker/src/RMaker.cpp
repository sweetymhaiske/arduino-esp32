#include "RMaker.h"
#include <esp_err.h>
#include "WiFi.h"
#include <esp_wifi.h>

extern bool tcpipInit();
#undef IPADDR_NONE
static EventGroupHandle_t wifi_event_group;

/* Event handler for catching RainMaker events */
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

void RMakerClass::init(char *node_name, char *node_type)
{
    if(tcpipInit() == false){
        log_e("TCP/IP init fail");
        return;
    }
    wifi_event_group = xEventGroupCreate();

    esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL);
    
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    esp_err_t err = esp_wifi_init(&cfg);
    if(err != ESP_OK){
        log_e("WiFi init fail");
        return;
    }

    esp_rmaker_config_t rainmaker_cfg;
    rainmaker_cfg.info.name = node_name;
    rainmaker_cfg.info.type = node_type;
    rainmaker_cfg.info.fw_version = "1.0";
    rainmaker_cfg.info.model = "Rain"; 
    rainmaker_cfg.enable_time_sync = false;
 
    err = esp_rmaker_init(&rainmaker_cfg);
    if (err != ESP_OK) {
        log_e("Could not initialise ESP RainMaker. Aborting!!!");
           vTaskDelay(5000/portTICK_PERIOD_MS);
           abort();
    }   
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
