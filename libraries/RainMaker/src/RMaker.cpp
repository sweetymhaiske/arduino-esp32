#include "RMaker.h"
#include "WiFi.h"
#include <esp_wifi.h>
#include <esp_rmaker_user_mapping.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp_rmaker_standard_params.h>
#include <esp_rmaker_schedule.h>

static esp_err_t err;

void RMakerClass::enableRainMaker()
{
    rainMakerEnable = true;
}

bool RMakerClass::isRainMakerEnabled()
{
    return rainMakerEnable;
}

static void event_handler(void *arg, esp_event_base_t event_base, int event_id, void *event_data)
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
    }   
}

void RMakerClass::setTimeSync(bool val)
{
    rainmaker_cfg.enable_time_sync = val;
}

Node RMakerClass::initNode(const char *name, const char *type)
{
    Node node;
    enableRainMaker();

    esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);

    esp_rmaker_node_t *rnode = NULL;
    rnode = esp_rmaker_node_init(&rainmaker_cfg, name, type);
    if (!rnode){
        log_e("Node init failed");
        return node;
    }
    node.setNodeHandle(rnode);
    return node;
}

esp_err_t RMakerClass::start()
{
    err = esp_rmaker_start();    
    if(err != ESP_OK){
        log_e("ESP RainMaker core task failed");
    }
    return err;
}

esp_err_t RMakerClass::stop()
{
    err = esp_rmaker_stop();
    if(err != ESP_OK) {
        log_e("ESP RainMaker stop error");
    }
    return err;
}

esp_err_t RMakerClass::deinitNode(Node rnode)
{
    err = esp_rmaker_node_deinit(rnode.getNodeHandle());
    if(err != ESP_OK) {
        log_e("Node deinit failed");
    }
    return err;
}

esp_err_t RMakerClass::enableSchedule()
{
    err = esp_rmaker_schedule_enable();
    if(err != ESP_OK) {
        log_e("Schedule enable failed");
    }
    return err;
}

esp_err_t RMakerClass::enableOTA(ota_type_t type)
{
    esp_rmaker_ota_config_t ota_config;
    ota_config.server_cert = ESP_RMAKER_OTA_DEFAULT_SERVER_CERT;
    err = esp_rmaker_ota_enable(&ota_config, type);
    if(err != ESP_OK) {
        log_e("OTA enable failed");
    }
    return err;
}

RMakerClass RMaker;
