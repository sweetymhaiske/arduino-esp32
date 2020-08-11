#include "RMaker.h"
#include "WiFi.h"
#include <esp_wifi.h>
#include <esp_rmaker_user_mapping.h>
#include <esp_rmaker_core.h>
#include <esp_err.h>
#include <esp_rmaker_standard_params.h>
static esp_err_t err;
extern bool tcpipInit();

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
    } else {
        log_i("Invalid event received!");
    }   
}

void RMakerClass::setTimeSync(bool val)
{
    rainmaker_cfg.enable_time_sync = val;
}

esp_rmaker_node_t* RMakerClass::initNode(const char *node_name, const char *node_type)
{
    enableRainMaker();
    if(tcpipInit() == false) {
        log_e("TCP/IP init fail");   
    }
    
    esp_event_handler_register(WIFI_PROV_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_event_handler_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &event_handler, NULL);
    
    esp_event_handler_register(RMAKER_EVENT, ESP_EVENT_ANY_ID, &event_handler, NULL);
    esp_rmaker_node_t *node = NULL;
    node = esp_rmaker_node_init(&rainmaker_cfg, node_name, node_type);
    if (!node){
        log_e("Could not initialise Node.");
        return NULL;
    }
    return node;
}

void RMakerClass::start()
{
    err = esp_rmaker_start();    
    if(err != ESP_OK){
        log_e("ESP RainMaker core task fail");
        return;
    }
    WiFi.beginProvision(WIFI_PROV_SCHEME_SOFTAP, WIFI_PROV_SCHEME_HANDLER_NONE, WIFI_PROV_SECURITY_1, "abcd1234", "PROV_123"); 
}

void RMakerClass::stop()
{
    err = esp_rmaker_stop();
    if(err != ESP_OK) {
        log_e("ESP RainMaker stop error");
    }
}

void RMakerClass::deinitNode(const esp_rmaker_node_t *node)
{
    err = esp_rmaker_node_deinit(node);
    if(err != ESP_OK) {
        log_e("Node deinit fail");
    }
}

const esp_rmaker_node_t* RMakerClass::getNode()
{
    return esp_rmaker_get_node();
}

char* RMakerClass::getNodeID()
{
    return esp_rmaker_get_node_id();
}

esp_rmaker_node_info_t* RMakerClass::getNodeInfo()
{
    return esp_rmaker_node_get_info(getNode());
}

esp_err_t RMakerClass::addNodeAttr(const char *attr_name, const char *val)
{
    err = esp_rmaker_node_add_attribute(getNode(), attr_name, val);
    if(err != ESP_OK) {
        log_e("Failed to add attribute to the Node");
        return err;
    }
    return ESP_OK;
}

esp_err_t RMakerClass::addNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device)
{
    err = esp_rmaker_node_add_device(node, device.getDeviceHandle());
    if(err != ESP_OK){
        log_e("Device was not added to the Node");
        return err;
    }
    return ESP_OK;
}

esp_err_t RMakerClass::removeNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device)
{
    err = esp_rmaker_node_remove_device(node, device.getDeviceHandle());
    if(err != ESP_OK){
        log_e("Device was not added to the Node");
        return err;
    }   
    return ESP_OK;
}

RMakerClass RMaker;
