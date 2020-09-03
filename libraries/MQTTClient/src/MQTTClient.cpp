#include "MQTTClient.h"
#include <esp32-hal-log.h>
#include <mqtt_client.h>
esp_mqtt_client_config_t mqtt_cfg;
//over TCP
void MQTTClient::begin(const char *url, esp_err_t (*mqtt_event_handler)(Mqtt_Event_Handle)) 
{
    mqtt_cfg.uri = url;
    mqtt_cfg.event_handle = mqtt_event_handler;
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

//over SSL
void MQTTClient::begin(const char *url, const char *broker_cert, esp_err_t (*mqtt_event_handler)(Mqtt_Event_Handle))
{
    mqtt_cfg.uri = url;
    mqtt_cfg.event_handle = mqtt_event_handler;
    mqtt_cfg.cert_pem = broker_cert;
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

//over SSL
void MQTTClient::begin(const char *url, const char *client_cert, const char *client_key, esp_err_t (*mqtt_event_handler)(Mqtt_Event_Handle))
{
    mqtt_cfg.uri = url;
    mqtt_cfg.event_handle = mqtt_event_handler;
    mqtt_cfg.client_cert_pem = client_cert;
    mqtt_cfg.client_key_pem = client_key;
    esp_mqtt_client_handle_t client = esp_mqtt_client_init(&mqtt_cfg);
    esp_mqtt_client_start(client);
}

int MQTTClient::clientPublish(Mqtt_Client_Handle client, const char *topic, const char *data, int len, int qos, int retain)
{
    return esp_mqtt_client_publish(client, topic, data, len, qos, retain);
}

int MQTTClient::clientSubscribe(Mqtt_Client_Handle client, const char *topic, int qos)
{
    return esp_mqtt_client_subscribe(client, topic, qos);
}

int MQTTClient::clientUnsubscribe(Mqtt_Client_Handle client, const char *topic)
{   
    return esp_mqtt_client_unsubscribe(client, topic);
}

