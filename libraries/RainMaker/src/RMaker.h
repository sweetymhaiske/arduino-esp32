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
        esp_err_t deinitNode(Node node);
        esp_err_t enableSchedule();
        esp_err_t enableOTA(ota_type_t type);

        esp_err_t start();
        esp_err_t stop();
};

extern RMakerClass RMaker;
