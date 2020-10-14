#include "Arduino.h"

#include "RMakerType.h"
#include "RMakerNode.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass
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
        bool isRainMakerEnabled();

        void setTimeSync(bool val);
        Node initNode(const char *name, const char *type);
        void deinitNode(Node node);
        void enableSchedule();
        esp_err_t enableOTA(ota_type_t type);

        void start();
        void stop();
};

extern RMakerClass RMaker;
