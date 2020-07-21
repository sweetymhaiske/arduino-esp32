#include "RMaker.h"
#include <esp_err.h>
#undef IPADDR_NONE

void RMakerClass::init(char *node_name, char *node_type)
{
    esp_rmaker_config_t rainmaker_cfg = { 
        .info = { 
            .name = node_name,
            .type = node_type,
        },
        .enable_time_sync = false,
    };  
    esp_err_t err = esp_rmaker_init(&rainmaker_cfg);
    if (err != ESP_OK) {
        log_e("Could not initialise ESP RainMaker. Aborting!!!");
    }   
}

esp_err_t RMakerClass::start()
{
    return esp_rmaker_start();    
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
