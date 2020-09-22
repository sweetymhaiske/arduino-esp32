# MultiSwitch Example
- It demonstrate the priv_data for callback

## Compile n Flash firmware

### ESP32-S2 Board
- SelfClaiming + SOFTAP provisioning

### ESP32 Board
- Assisted claiming + BLE provisioning

## What to expect in this sketch ?

- Three switch are connected to GPIO_0, GPIO_16 and GPIO_17.
- Pressing the BOOT button toggles the status of switch connected at GPIO_0
- Toggling the power button for switch devices on phone app will update the status to RainMaker cloud if `RMaker.updateAndReportParam()` API is called and print the status on Serial monitor.

### Output
```
[I][RMaker.cpp:27] event_handler(): RainMaker Initialised.
[I][WiFiProv.cpp:190] beginProvision(): Aleardy Provisioned
[I][WiFiProv.cpp:194] beginProvision(): Attempting connect to AP: Wce*****

Received value = false for switch3 - power
Switch at pin : 17
Received value = false for switch2 - power
Switch at pin : 16
Received value = false for switch1 - power
Switch at pin : 0
Received value = true for switch1 - power
Switch at pin : 0
Received value = true for switch2 - power
Switch at pin : 16

[I][RMakerGeneric.cpp:213] updateAndReportParam(): Device : switch1, Param Name : power, Val : false
[I][RMakerGeneric.cpp:213] updateAndReportParam(): Device : switch1, Param Name : power, Val : true

```

