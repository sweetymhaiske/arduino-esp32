#include "WiFi.h"
#include "MQTTClient.h"

const char* ssid     = "Wce*****";
const char* password = "123456789";
const char* url = "mqtts://mqtt.eclipse.org:8883";
const char *broker_cert = "-----BEGIN CERTIFICATE-----\n" \
"MIIEkjCCA3qgAwIBAgIQCgFBQgAAAVOFc2oLheynCDANBgkqhkiG9w0BAQsFADA/\n" \
"MSQwIgYDVQQKExtEaWdpdGFsIFNpZ25hdHVyZSBUcnVzdCBDby4xFzAVBgNVBAMT\n" \
"DkRTVCBSb290IENBIFgzMB4XDTE2MDMxNzE2NDA0NloXDTIxMDMxNzE2NDA0Nlow\n" \
"SjELMAkGA1UEBhMCVVMxFjAUBgNVBAoTDUxldCdzIEVuY3J5cHQxIzAhBgNVBAMT\n" \
"GkxldCdzIEVuY3J5cHQgQXV0aG9yaXR5IFgzMIIBIjANBgkqhkiG9w0BAQEFAAOC\n" \
"AQ8AMIIBCgKCAQEAnNMM8FrlLke3cl03g7NoYzDq1zUmGSXhvb418XCSL7e4S0EF\n" \
"q6meNQhY7LEqxGiHC6PjdeTm86dicbp5gWAf15Gan/PQeGdxyGkOlZHP/uaZ6WA8\n" \
"SMx+yk13EiSdRxta67nsHjcAHJyse6cF6s5K671B5TaYucv9bTyWaN8jKkKQDIZ0\n" \
"Z8h/pZq4UmEUEz9l6YKHy9v6Dlb2honzhT+Xhq+w3Brvaw2VFn3EK6BlspkENnWA\n" \
"a6xK8xuQSXgvopZPKiAlKQTGdMDQMc2PMTiVFrqoM7hD8bEfwzB/onkxEz0tNvjj\n" \
"/PIzark5McWvxI0NHWQWM6r6hCm21AvA2H3DkwIDAQABo4IBfTCCAXkwEgYDVR0T\n" \
"AQH/BAgwBgEB/wIBADAOBgNVHQ8BAf8EBAMCAYYwfwYIKwYBBQUHAQEEczBxMDIG\n" \
"CCsGAQUFBzABhiZodHRwOi8vaXNyZy50cnVzdGlkLm9jc3AuaWRlbnRydXN0LmNv\n" \
"bTA7BggrBgEFBQcwAoYvaHR0cDovL2FwcHMuaWRlbnRydXN0LmNvbS9yb290cy9k\n" \
"c3Ryb290Y2F4My5wN2MwHwYDVR0jBBgwFoAUxKexpHsscfrb4UuQdf/EFWCFiRAw\n" \
"VAYDVR0gBE0wSzAIBgZngQwBAgEwPwYLKwYBBAGC3xMBAQEwMDAuBggrBgEFBQcC\n" \
"ARYiaHR0cDovL2Nwcy5yb290LXgxLmxldHNlbmNyeXB0Lm9yZzA8BgNVHR8ENTAz\n" \
"MDGgL6AthitodHRwOi8vY3JsLmlkZW50cnVzdC5jb20vRFNUUk9PVENBWDNDUkwu\n" \
"Y3JsMB0GA1UdDgQWBBSoSmpjBH3duubRObemRWXv86jsoTANBgkqhkiG9w0BAQsF\n" \
"AAOCAQEA3TPXEfNjWDjdGBX7CVW+dla5cEilaUcne8IkCJLxWh9KEik3JHRRHGJo\n" \
"uM2VcGfl96S8TihRzZvoroed6ti6WqEBmtzw3Wodatg+VyOeph4EYpr/1wXKtx8/\n" \
"wApIvJSwtmVi4MFU5aMqrSDE6ea73Mj2tcMyo5jMd6jmeWUHK8so/joWUoHOUgwu\n" \
"X4Po1QYz+3dszkDqMp4fklxBwXRsW10KXzPMTZ+sOPAveyxindmjkW8lGy+QsRlG\n" \
"PfZ+G6Z6h7mjem0Y+iWlkYcV4PIWL1iwBi8saCbGS5jN2p8M+X+Q7UNKEkROb3N6\n" \
"KOqkqm57TH2H3eDJAkSnh6/DNFu0Qg==\n" \
"-----END CERTIFICATE-----";

MQTTClient mqtt;
static esp_err_t mqttEventHandler(Mqtt_Event_Handle event)
{
    Mqtt_Client_Handle client = event->client;
    int msg_id;
    
    switch(event->event_id){
        case MQTT_EVENT_CONNECTED:
            Serial.println("Mqtt Connected");
            msg_id = mqtt.clientPublish(client, "/topic/qos1", "data_3", 0, 1, 0);
            Serial.printf("Sent publish successful, msg_id = %d\n", msg_id);

            msg_id = mqtt.clientSubscribe(client, "/topic/qos0", 0);
            Serial.printf("Sent subscribe successful, msg_id = %d\n", msg_id);
            
            break;
        case MQTT_EVENT_DISCONNECTED:
            Serial.println("Mqtt Disconnected");
            break;
        case MQTT_EVENT_SUBSCRIBED:
            Serial.printf("Mqtt Subscribed, msg_id=%d\n", event->msg_id);
            msg_id = mqtt.clientPublish(client, "/topic/qos0", "data", 0, 0, 0); 
            Serial.printf("Sent publish successful, msg_id=%d\n", msg_id);
            break;
        case MQTT_EVENT_UNSUBSCRIBED:
            Serial.printf("Mqtt Unsubcribed, msg_id=%d\n", event->msg_id);
            break;
        case MQTT_EVENT_PUBLISHED:
            Serial.printf("Mqtt Published, msg_id=%d\n", event->msg_id);
            break;
        case MQTT_EVENT_DATA:
            Serial.println("Mqtt Data");
            Serial.printf("TOPIC=%.*s\r\n", event->topic_len, event->topic);
            Serial.printf("DATA=%.*s\r\n", event->data_len, event->data);
            break;
        default:
            break;
    }
    return ESP_OK;
}

void setup()
{
    Serial.begin(115200);
    delay(10);

    //Connecting to WiFi network
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    //MQTT over SSL
    mqtt.begin(url, broker_cert, mqttEventHandler);
}
void loop()
{
}
