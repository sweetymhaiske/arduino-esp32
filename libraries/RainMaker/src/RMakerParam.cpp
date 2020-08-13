#include "RMakerParam.h"
#include <esp_err.h>
#include <esp32-hal.h>

static esp_err_t err;

void Param::createParam(const char *param_name, const char *param_type, param_val_t val, uint8_t properties)
{
    param = esp_rmaker_param_create(param_name, param_type, val, properties);
} 

void Param::addUIType(const char *ui_type)
{
    err = esp_rmaker_param_add_ui_type(param, ui_type);
    if(err != ESP_OK) {
        log_e("Add UI type error");
    }
}

void Param::addBounds(param_val_t min, param_val_t max, param_val_t step)
{
    err = esp_rmaker_param_add_bounds(param, min, max, step);
    if(err != ESP_OK) {
        log_e("Add Bounds error");
    }
}
