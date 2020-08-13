# API's Introduced in RainMaker library

## RainMaker NODE API's
 
### RMaker.initNode()
This API initialise the ESP RainMaker Node and WiFi, which also initialise the MAC address which will act as the unique node identifier (node_id) for ESP32-S2 self claiming.
```
RMaker.initNode(const char * node_name, const char * node_type);
```
* **Parameters Required**
1. `node_name`: Name of the Node
2. `node_type`: Type of the Node

* **Return Type**
1. `node_t` : On success
2. `NULL` : On failure
> NOTE : You can also set the configuration of node using following API's
> - RMaker.setTimeSync()

### RMaker.start()
This API starts the RainMaker core task which will wait for Wi-Fi, do the claiming, if required, connect to the RainMaker cloud over MQTT, report the node configuration, report the values of parameters, and then wait for commands.
If the ESP32 is already provisioned, it will join the configured Wi-Fi network. Else, it will start the Wi-Fi provisioning. 
```
RMaker.start()
```
> NOTE : Rainmaker should be initialised before this call.

### RMaker.stop()
This API stop the RainMaker core task.

### RMaker.deinitNode()
This API deinitialise the ESP RainMaker Node created using `RMaker.initNode()`.
```
RMaker.deinitNode(node_t node)
```
* **Parameters Required**
1. `node` : Node Handle created using `RMaker.intiNode()`

### RMaker.getNodeID()
This API returns the unique NODE ID assigned to the Node. This NODE ID is usually the MAC address of the Node.
```
RMaker.getNodeID()
```
* **Return Type**
1. `char *` : Pointer to a NULL terminated Node ID string.

### RMaker.addNodeAttr()
This API adds a new attribute as the metadata for the node.
```
RMaker.addNodeAttr(const char *attr_name, const char *val);
```
* **Parameters Required**
1. `attr_name` : Name of the attribute
2. `val` : Value of the attribute

* **Return Type**
1. `ESP_OK` : On success
2. Error in case of failure
> NOTE : For the sake of simplicity, only string values are allowed.

### RMaker.addNodeDevice()
This API add device to the Node.
```
RMaker.addNodeDevice(const node_t node, RMakerGenericClass device);
```
* **Parameters Passed**
1. `node` : Node Handle of node created using RMaker.initNode()
2. `device` : Device object

* **Return Type**
1. `ESP_OK` : On success
2. Error in case of failure
> NOTE : 
> - This is the mandatory API to register device to node.
> - Single Node can have multiple devices

### RMaker.addRemoveDevice()
This API remove the device added to the Node.
```
RMaker.removeNodeDevice(const node_t node, RMakerGenericClass device);
```
* **Parameters Passed**
1. `node` : Node Handle of node created using RMaker.initNode()
2. `device` : Device object

* **Return Type**
1. `ESP_OK` : On success
2. Error in case of failure
> NOTE : 
> - This is the mandatory API to register device to node.
> - Single Node can have multiple devices

### RMaker.updateAndReportParam()
This API will update the parameter on the device and report it to ESP RainMaker cloud
```
RMaker.updateAndReportParam()
```
> NOTE :
> - This API should always be called inside device write callback, if you aimed at updating n reporting parameter values changed via RainMaker Client, to the ESP RainMaker cloud.
> - If not called then paramter values will not be updated to the ESP RainMaker cloud.

## RainMaker DEVICE API's
`Device` class exposes the API's for device.
> NOTE : my_device is object of Device class.

### createDevice()
This API creates the virtual device. It could be something like "Switch", "LightBulb" etc.
```
my_device.createDevice(const char *dev_name, const char *dev_type, void *priv_data);
```
* **Parameters Required**
1. `dev_name` : Unique device name
2. `dev_type` : Optional device type. It can be kept NULL.
    * Standard Device Types
        * ESP_RMAKER_DEVICE_SWITCH
        * ESP_RMAKER_DEVICE_LIGHTBULB
        * ESP_RMAKER_DEVICE_FAN
        * ESP_RMAKER_DEVICE_TEMP_SENSOR   
3. `priv_data` : Private data associated with the device. This will be passed to the callbacks.

> NOTE : This created device should be added to the node using `RMaker.addNodeDevice(my_node, my_device)`.

### addDeviceAttr()
This API adds device attribute.
```
my_device.addDeviceAttr(const char *attr_name, const char *val);
```
* **Parameters Required**
1. `attr_name` : Name of attribute
2. `val` : Value of attribute

* **Return Type**
1. `ESP_OK` : On success
2. Error on failure

> NOTE : Device attributes are reported only once after a boot-up as part of the node configuration. Eg. Serial Number

### deleteDevice()
This API deletes the device created on node.
```
my_device.deleteDevice();
```

### addXParam()
This API adds standard parameter to the device.
> Note : X is the name of parameter
* **Standard Parameters**
These are the standard parameters.
    * name : ESP_RMAKER_DEF_NAME_PARAM
    * power : ESP_RMAKER_DEF_POWER_NAME
    * brightness : ESP_RMAKER_DEF_BRIGHTNESS_NAME
    * hue : ESP_RMAKER_DEF_HUE_NAME
    * saturation : ESP_RMAKER_DEF_SATURATION_NAME
    * intensity : ESP_RMAKER_DEF_INTENSITY_NAME
    * cct : ESP_RMAKER_DEF_CCT_NAME 
    * direction : ESP_RMAKER_DEF_DIRECTION_NAME
    * speed : ESP_RMAKER_DEF_SPEED_NAME
    * temperature : ESP_RMAKER_DEF_TEMPERATURE_NAME
```
my_device.addNameParam();
my_device.addPowerParam(bool val);
my_device.addBrightnessParam(int val);    
my_device.addHueParam(int val);
my_device.addSaturationParam(int val);
my_device.addIntensityParam(int val);
my_device.addCctParam(int val);
my_device.addDirectionParam(int val);
my_device.addSpeedParam(int val);
my_device.addTempratureParam(float val);
```
* **Paramters passed**
Value need for the parameter.

> NOTE : Care should be taken while accessing name of parameter. Above mentioned are the two ways using which parameters can be accessed. Either LHS or RHS.

### assignPrimaryParam()
This API Assign a parameter (already added using addXParam()) as a primary parameter, which can be used by clients (phone apps specifically) to give prominence to it.
```
my_device.assignPrimaryParam(char *param_name);
```
* **Parameter Required**
1. `param_name` : Name of the parameter.

### addParam()
This API allows user to add custom parameter to the device created using `Param` class, according to there ease.
```
my_device.addParam(Param parameter);
```
* **Parameter Required**
1. `parameter` : Object of Param
> NOTE : Param class exposes API's to create the custom parameter.

# Standard Predefined Types
API's are exposed for standard services, standard parameters n standard ui elements.
Using it user can create standard devices.

- Switch
- LightBulb
- TemperatureSensor
- Fan
> NOTE: The care should be taken that the RMaker.init() should be the first API call and RMaker.start() should be the last one. Device API should be called in between.

n
