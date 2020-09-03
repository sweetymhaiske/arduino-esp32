#include <esp_err.h>
#include <mqtt_client.h>

typedef esp_mqtt_event_handle_t Mqtt_Event_Handle;
typedef esp_mqtt_client_handle_t Mqtt_Client_Handle;

class MQTTClient
{
public:
       
    void begin(const char *uri, esp_err_t (*mqtt)(Mqtt_Event_Handle));  
    void begin(const char *uri, const char *cert, esp_err_t (*mqtt)(Mqtt_Event_Handle));
    void begin(const char *uri, const char *client_cert, const char *client_key, esp_err_t (*mqtt)(Mqtt_Event_Handle));
    int clientPublish(Mqtt_Client_Handle client, const char *topic, const char *data, int len, int qos, int retain);
    int clientSubscribe(Mqtt_Client_Handle client, const char *topic, int qos);
    int clientUnsubscribe(Mqtt_Client_Handle client, const char *topic);
};
