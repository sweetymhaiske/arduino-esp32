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
        log_e("Could not initialise Node.");
        return node;
    }
    node.setNodeHandle(rnode);
    return node;
}

void RMakerClass::start()
{
    err = esp_rmaker_start();    
    if(err != ESP_OK){
        log_e("ESP RainMaker core task fail");
        return;
    }
}

void RMakerClass::stop()
{
    err = esp_rmaker_stop();
    if(err != ESP_OK) {
        log_e("ESP RainMaker stop error");
    }
}

void RMakerClass::deinitNode(Node rnode)
{
    err = esp_rmaker_node_deinit(rnode.getNodeHandle());
    if(err != ESP_OK) {
        log_e("Node deinit fail");
    }
}

void RMakerClass::enableSchedule()
{
    err = esp_rmaker_schedule_enable();
    if(err != ESP_OK) {
        log_e("Schedule enable fail");
    }
}

esp_err_t RMakerClass::enableOTA(ota_type_t type)
{
    esp_rmaker_ota_config_t ota_config;
    ota_config.server_cert = ESP_RMAKER_OTA_DEFAULT_SERVER_CERT;
    return esp_rmaker_ota_enable(&ota_config, type);
}

RMakerClass RMaker;
