#include "Arduino.h"

#include "RMakerType.h"
#include "RMakerOTA.h"
#include "RMakerDevice.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass : public RMakerOTAClass
{
    private:
        esp_rmaker_config_t rainmaker_cfg = {false};
    
    protected:
        bool rainMakerEnable;

    public:
        RMakerClass() {
            rainMakerEnable = false;
        }
        
        void enableRainMaker();
        bool isRainMakerEnable();
        void setTimeSync(bool val);
        esp_rmaker_node_t* initNode(const char *node_name, const char *node_type);
        void start();
        void stop();
        void deinitNode(const esp_rmaker_node_t *node);
        const esp_rmaker_node_t* getNode();
        char* getNodeID();
        esp_rmaker_node_info_t *getNodeInfo();
        esp_err_t addNodeAttr(const char *attr_name, const char *val);
        esp_err_t addNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device);
        esp_err_t removeNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device);  
};

extern RMakerClass RMaker;
