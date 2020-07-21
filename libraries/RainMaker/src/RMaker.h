#include "Arduino.h"

#include "RMakerType.h"
#include "RMakerOTA.h"
#include "RMakerDevice.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass : public RMakerOTAClass
{
    public:
        void init(char *node_name, char *node_type);
        esp_err_t start();
        esp_err_t stop();

        char *getNodeID();
        esp_rmaker_node_info_t *getNodeInfo();
        esp_err_t addNodeAttr(const char *attr_name, const char *val);
};

extern RMakerClass RMaker;
