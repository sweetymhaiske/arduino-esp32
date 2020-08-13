#include "Arduino.h"

#include "RMakerType.h"
#include "RMakerOTA.h"
#include "RMakerDevice.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass : public RMakerOTAClass, public Param
{
    private:
        esp_rmaker_config_t rainmaker_cfg = {false};
        bool updateParam;
 
    protected:
        bool rainMakerEnable;
   
    public:
        RMakerClass() {
            rainMakerEnable = false;
            updateParam = false;
        }
        
        void setUpdateParam(bool val)
        {
            updateParam = val;
        }       
    
        bool getUpdateParam()
        {
            return updateParam;
        }

        void enableRainMaker();
        bool isRainMakerEnabled();

        void setTimeSync(bool val);
        node_t initNode(const char *node_name, const char *node_type);
        void deinitNode(const esp_rmaker_node_t *node);

        void start();
        void stop();

        const esp_rmaker_node_t* getNode();
        char* getNodeID();
        esp_rmaker_node_info_t *getNodeInfo();
        esp_err_t addNodeAttr(const char *attr_name, const char *val)
;
        void updateAndReportParam();

        esp_err_t addNodeDevice(const node_t node, RMakerGenericClass device);
        esp_err_t removeNodeDevice(const node_t node, RMakerGenericClass device);  
};

extern RMakerClass RMaker;
