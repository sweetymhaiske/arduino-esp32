#include <esp_err.h>
#include "RMakerType.h"

class RMakerOTAClass
{
    public:
        esp_err_t enableOTA(OTAType_t type);
};
