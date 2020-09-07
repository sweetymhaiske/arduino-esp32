#include "RMaker.h"
#include <esp_rmaker_user_mapping.h>
#include <qrcode.h>

#define PROV_QR_VERSION "v1"
#define PROV_TRANSPORT_SOFTAP   "softap"
#define PROV_TRANSPORT_BLE      "ble"
#define QRCODE_BASE_URL     "https://rainmaker.espressif.com/qrcode.html"

static void print_qr(const char *name, const char *pop, const char *transport)
{
    if (!name || !pop || !transport) {
        log_w("Cannot generate QR code payload. Data missing.");
        return;
    }
    char payload[150];
    snprintf(payload, sizeof(payload), "{\"ver\":\"%s\",\"name\":\"%s\"" \
                    ",\"pop\":\"%s\",\"transport\":\"%s\"}",
                    PROV_QR_VERSION, name, pop, transport);
    log_i("Scan this QR code from the phone app for Provisioning.");
    qrcode_display(payload);
    ESP_LOGI(TAG, "If QR code is not visible, copy paste the below URL in a browser.\n%s?data=%s", QRCODE_BASE_URL, payload);
}

