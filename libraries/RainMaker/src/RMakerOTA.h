#include <esp_err.h>
#include "RMakerType.h"

class RMakerOTAClass
{
    public:
        esp_err_t enableOTA(ota_type_t type);
};
