#include <esp_rmaker_core.h>
#include <esp_rmaker_ota.h>

typedef esp_rmaker_node_t* node_t;
typedef esp_rmaker_node_info_t node_info_t;
typedef esp_rmaker_param_val_t param_val_t;
typedef esp_rmaker_write_ctx_t write_ctx_t;
typedef esp_rmaker_read_ctx_t read_ctx_t;
typedef esp_rmaker_device_t device_handle_t;
typedef esp_rmaker_param_t param_handle_t;
typedef esp_rmaker_ota_type_t ota_type_t;

typedef void (*deviceWriteCb)(const char *device, const char *param, const param_val_t val, void *priv_data, write_ctx_t *ctx);

typedef void (*deviceReadCb)(const char *device, const char *param, void *priv_data, read_ctx_t *ctx); 

#define PARAMS 13

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
