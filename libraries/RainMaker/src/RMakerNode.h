#include "RMakerDevice.h"
#include <esp_rmaker_core.h>
class Node
{
    private:
        esp_rmaker_node_t *node;
    public:
        Node()
        {
            node = NULL;
        }

        void setNodeHandle(esp_rmaker_node_t *rnode)
        {
            node = rnode;
        }
        esp_rmaker_node_t *getNodeHandle()
        {
            return node;
        }
    
        esp_err_t addDevice(RMakerGenericClass device);
        esp_err_t removeDevice(RMakerGenericClass device);

        char* getNodeID();
        esp_rmaker_node_info_t* getNodeInfo();
        esp_err_t addNodeAttr(const char *attr_name, const char *val);
};
