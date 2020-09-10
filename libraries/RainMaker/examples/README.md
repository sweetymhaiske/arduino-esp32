# API's Introduced in RainMaker Library

## RainMaker Agent API
 
### RMaker.initNode()
This API initializes and creates ESP RainMaker Node and initialize WiFi. 
```
RMaker.initNode(const char * node_name, const char * node_type);
```
* **Parameters**
1. `node_name`: Name of the node
2. `node_type`: Type of the node

* **Return**
1. `Node` : On success
2. `NULL` : On failure

> NOTE : This should be the first call before using any other ESP RainMaker API. 
* You can also set the configuration of node using following API's
 1. RMaker.setTimeSync()
> NOTE : If you want to set the configuration for the node then the above API should be called first and then `RMaker.initNode()`.

### RMaker.start()
It performs provisioning and starts the ESP RainMaker Agent.
```
RMaker.start()
```
> NOTE : ESP Rainmaker Agent should be initialized before this call.
> Once ESP RainMaker Agent starts, compulsorily call WiFi.beginProvision() API.

### RMaker.stop()
It stops the ESP RainMaker Agent which was started using `RMaker.start()`.
```
RMaker.stop()
```

### RMaker.deinitNode()
It deinitialize the ESP RainMaker Node created using `RMaker.initNode()`.
```
RMaker.deinitNode(Node node)
```
* **Parameter**
1. `node` : Node object created using `RMaker.intiNode()`

### RMaker.updateAndReportParam()
It update the parameter on the device and report it to ESP RainMaker cloud.
```
RMaker.updateAndReportParam()
```
> NOTE :
> - This API should always be called inside device write callback, if you aimed at updating n reporting parameter values, changed via RainMaker Client (Phone App), to the ESP RainMaker cloud.
> - If not called then paramter values will not be updated to the ESP RainMaker cloud.

### RMaker.enableOTA()
It enables OTA as per ESP RainMaker Specification. For more details refer ESP RainMaker documentation.
```
RMaker.enableOTA(ota_type_t type);
```
* **Parameter**
1. `type` : OTA workflow type.
    - OTA_USING_PARAMS
    - OTA_USING_TOPICS


## RainMaker Node API's
`Node` class exposes the API's for node.
> NOTE : my_node is the object of Node class.

### getNodeID()
It returns the unique node_id assigned to the node. This node_id is usually the MAC address of the node.
```
my_node.getNodeID()
```
* **Return**
1. `char * ` : Pointer to a NULL terminated node_id string.

### getNodeInfo()
It returns pointer to the node_info_t as configured during node initialisation.
```
my_node.getNodeInfo();
```
* **Return**
1. `node_info_t` : Pointer to the structure node_info_t on success.
2. `NULL` : on failure

### addNodeAttr()
It adds a new attribute as the metadata for the node.
```
my_node.addNodeAttr(const char *attr_name, const char *val);
```
* **Parameters**
1. `attr_name` : Name of the attribute
2. `val` : Value of the attribute

* **Return**
1. `ESP_OK` : On success
2. Error in case of failure
> NOTE : Only string values are allowed.

### addDevice()
It adds device created using `createDevice()` of using `Standard class` to the node.
```
my_node.addDevice(RMakerGenericClass device);
```
* **Parameter**
1. `device` : Device object

* **Return**
1. `ESP_OK` : On success
2. Error in case of failure
> NOTE : 
> - This is the mandatory API to register device to node.
> - Single Node can have multiple devices.
> - Device name should be unique for each device.

### removeDevice()
It removes device from the node.
```
my_node.removeNodeDevice(RMakerGenericClass device);
```
* **Parameter**
1. `device` : Device object

* **Return**
1. `ESP_OK` : On success
2. Error in case of failure

## RainMaker DEVICE API's
`Device` class exposes the API's for device.
> NOTE : my_device is the object of Device class.

### createDevice()
It creates the virtual device. It could be something like "Switch", "LightBulb" etc.
```
my_device.createDevice(const char *dev_name, const char *dev_type, void *priv_data);
```
* **Parameters**
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
It adds new attribute to the device.
```
my_device.addDeviceAttr(const char *attr_name, const char *val);
```
* **Parameters**
1. `attr_name` : Name of the attribute
2. `val` : Value of the attribute

* **Return**
1. `ESP_OK` : On success
2. Error in case  of failure

> NOTE : Device attributes are reported only once after a boot-up as part of the node configuration. Eg. Serial Number

### deleteDevice()
It deletes the device created using `RMaker.createDevice()`.
```
my_device.deleteDevice();
```
* **Return**
1. `ESP_OK` : On success
2. Error in case of failure

### addXParam()
It adds standard parameter to the device.
> NOTE : X is the name of parameter
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
* **Standard Parameters**

* These are the standard parameters.
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
> NOTE : Care should be taken while accessing name of parameter. Above mentioned are the two ways using which parameters can be accessed. Either LHS or RHS.

### assignPrimaryParam()
It assigns a parameter (already added using addXParam()) as a primary parameter, which can be used by clients (phone apps specifically) to give prominence to it.
```
my_device.assignPrimaryParam(char * param_name);
my_device.assignPrimaryParam(Param p1);
```
* **Parameter**
1. `param_name` : Name of the parameter.

### addParam()
It allows user to add custom parameter to the device created using `Param` class.
```
my_device.addParam(Param parameter);
```
* **Parameter**
1. `parameter` : Object of Param
> NOTE : Param class exposes API's to create the custom parameter.

### updateAndReportParam()
It updates the parameter assosicated with particular device on ESP RainMaker cloud.
```
my_device.updateAndReportParam(const char * param_name, value);
```
* **Parameters**
1. `param_name` : Name of the parameter
2. `value` : Value to be updated. It can be int, bool, char * , float.

* **Return**
1. `ESP_OK` : On success
2. Error in case of failure

### addCb()
It registers read and write callback for the device which will be invoked as per requests received from the cloud (or other paths as may be added in future).
```
my_device.addCb(deviceWriteCb write_cb, deviceReadCb read_cb);
```
* **Parameters**
1. `write_cb` : Function with signature [ func_name(const char * device, const char * param_name, const param_val_t val, void * priv_data, write_ctx_t * ctx); ]
2. `read_cb` : Function with signature [ func_name(const char * device, const char * param_name, void * priv_data, read_ctx_t * ctx); ]

# Standard Device
- Classes are defined for the standard devices.
- Creating object of these class creates the standard device along with default parameters to it.
- Class for standard devices
    * Switch
    * LightBulb
    * TemperatureSensor
    * Fan
- Sample example
```
Switch switch1;
Switch switch2("switch2", NULL, true);
```
`"switch2"` : Name for standard device.

`NULL` : Private data for the device must be specified, which will be used in callback.

`true` : default value for the primary param, in case of switch it is power.

## RainMaker PARAM API's
`Param` class expose API for creating custom parameters for the devices.
> NOTE : my_param is the object of Param class.

### createParam()
It creates custom parameter.
```
my_param.createParam(const char *param_name, const char *param_type, param_val_t val, uint8_t properties);
``` 
* **Parameters**
1. `param_name` : Name for the parameter
2. `param_type` : Type for the parameter. It is optional can be kept NULL.
3. `val` : Define the default value for the parameter. It should be defined using `value(int ival)` , `value(bool bval)` , `value(float fval)` , `value(char *sval)`.
4. `properties` : Properties of the parameter, which will be a logical OR of flags.
    * Flags
        * PROP_FLAG_WRITE
        * PROP_FLAG_READ
        * PROP_FLAG_TIME_SERIES
        * PROP_FLAG_PERSIST

`Sample example : my_param.createParam("bright", NULL, value(30), PROP_FLAG_READ | PROP_FLAG_WRITE | PROP_FLAG_PERSIST);`
> NOTE : Parameter created using Param class should be added to the device using `my_device.addParam(my_param);`

### addUIType()
Add a UI type to the parameter
This will be used by the Phone apps (or other clients) to render appropriate UI for the given parameter. Please refer the RainMaker documetation for supported UI Types.
```
my_param.addUIType(const char * ui_type);
```
* **Paramters Required**
1. `ui_type` : String describing the UI Type.
    * Standard UI Types
     * ESP_RMAKER_UI_TOGGLE     
     * ESP_RMAKER_UI_SLIDER
     * ESP_RMAKER_UI_DROPDOWN
     * ESP_RMAKER_UI_TEXT  

### addBounds()
Add bounds for an integer/float parameter. This can be used to add bounds (min/max values) for a given integer parameter. Eg. brightness will have bounds as 0 and 100 if it is a percentage.
```
my_param.addBounds(param_val_t min, param_val_t max, param_val_t step);
```
* **Parameters Passed**
1. `min` : Minimum value
2. `max` : Maximum value
3. `step` : step Minimum stepping

`Sample example : my_param.addBounds(value(0), value(100), value(5));`

## RainMaker SERVICE API's
`Service` class exposes API's for service.
> NOTE : my_service is the object of Service class

### createService()
This API will create a "Service". It is exactly same like a device in terms of structure and so, all APIs for device are also valid for a service. A service could be something like OTA, diagnostics, etc.
```
my_service.createService(const char *serv_name, const char *serv_type, void *priv_data);
```
* **Parameters**
1. `serv_name` : The unique service name. Name of the service should not clash with device name.
2. `serv_type` : Service Type. It can be kept NULL.
3. `priv_data` : Private Data associated with the service will be passed to the callback. It can be kept NULL.
> NOTE : This service should be added to the node using `my_node.addDevice(my_service);`

### Standard Parameters for service
```
my_service.addOTAStatusParam();
my_service.addOTAInfoParam();
my_service.addOTAUrlParam();

```

## Standard Service
OTAService

 - This class is defined for standard OTA service.
 - Sample example
```
OTAService ota;
OTAService ota1("ota1", NULL);
```
`"ota1"` : It is the name of the service.

`NULL` : It is private data associated with the service which will be passed to the callback.

## NOTE
The care should be taken that the RMaker.initNode() should be the first API call and RMaker.start() should be the last one.
