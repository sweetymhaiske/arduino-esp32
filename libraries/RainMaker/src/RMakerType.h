#include <esp_rmaker_core.h>
#include <esp_rmaker_ota.h>

typedef esp_rmaker_node_t* Node;
typedef esp_rmaker_param_val_t param_val;
typedef esp_rmaker_write_ctx_t write_ctx;
typedef esp_rmaker_read_ctx_t read_ctx;
typedef esp_rmaker_device_t device_handle;
typedef esp_rmaker_param_t param_handle;

typedef esp_err_t (*deviceWriteCb)(const device_handle *device, const param_handle *param, const param_val val, void *priv_data, write_ctx *ctx);

typedef esp_err_t (*deviceReadCb)(const device_handle *device, const param_handle *param, void *priv_data, read_ctx *ctx); 

#define PARAMS 13

#define Param_t esp_rmaker_param_val_t
#define OTAType_t esp_rmaker_ota_type_t 
#define DEFAULT_SWITCH_POWER        true
#define DEFAULT_LIGHT_POWER         true
#define DEFAULT_LIGHT_BRIGHTNESS    25
#define DEFAULT_FAN_POWER           false
#define DEFAULT_FAN_SPEED           3
#define DEFAULT_TEMPERATURE         25.0
#define REPORTING_PERIOD            60 /* Seconds */

#define NAME_PARAM                  0
#define POWER_PARAM                 1
#define BRIGHTNESS_PARAM            2
#define HUE_PARAM                   3
#define SATURATION_PARAM            4
#define INTENSITY_PARAM             5
#define CCT_PARAM                   6
#define DIRECTION_PARAM             7
#define SPEED_PARAM                 8
#define TEMPERATURE_PARAM           9
#define STATUS_PARAM                10
#define INFO_PARAM                  11
#define URL_PARAM                   12
