#include "WiFi.h"
#include "MQTTClient.h"

const char* ssid     = "Wce*****";
const char* password = "123456789";
const char* url = "mqtts://test.mosquitto.org:8884";
const char* client_cert = ""; 
const char* client_key = "";

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

    //MQTT over SSL Mutual Auth
    mqtt.begin(url, client_cert, client_key, mqttEventHandler);
}
void loop()
{
}
