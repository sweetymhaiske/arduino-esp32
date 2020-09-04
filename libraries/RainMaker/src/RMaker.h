#include "Arduino.h"

#include "RMakerOTA.h"
#include "RMakerType.h"
#include "RMakerNode.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass : public RMakerOTAClass, public Param
{
    private:
        esp_rmaker_config_t rainmaker_cfg = {false};
        bool updateParam; //callback
 
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
        Node initNode(const char *node_name, const char *node_type);
        void deinitNode(Node node);

        void start();
        void stop();

        void updateAndReportParam();
};

extern RMakerClass RMaker;
