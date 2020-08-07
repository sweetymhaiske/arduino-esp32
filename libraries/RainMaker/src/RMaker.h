#include "Arduino.h"

#include "RMakerType.h"
#include "RMakerOTA.h"
#include "RMakerDevice.h"

#include <esp_rmaker_core.h>
#include <esp_rmaker_standard_types.h>

class RMakerClass : public RMakerOTAClass
{
    public:
        esp_rmaker_node_t *initNode(char *node_name, char *node_type);
        void deinitNode(const esp_rmaker_node_t *node);
        const esp_rmaker_node_t *getNode();
        void addNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device);
        void removeNodeDevice(const esp_rmaker_node_t *node, RMakerGenericClass device); 
        esp_err_t stop();
        void start();
        void updateAndReportParam(const param_handle *param, const param_val val);
        char *getParamName(const param_handle *param);
        char *getDeviceName(const device_handle *device);
        char *getNodeID();
        esp_rmaker_node_info_t *getNodeInfo();
        esp_err_t addNodeAttr(const char *attr_name, const char *val);
};

extern RMakerClass RMaker;
