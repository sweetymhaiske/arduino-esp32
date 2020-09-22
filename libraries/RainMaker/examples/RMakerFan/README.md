# Fan Example

## Compile n Flash firmware

### ESP32-S2 Board
- SelfClaiming + SOFTAP provisioning

### ESP32 Board
- Assisted claiming + BLE provisioning

## What to expect in this sketch ?

- Pressing the BOOT button will increase the speed by 1. The speed will cycle from 0 to 5 and then come back to 0.
- Toggling the power button for fan device on phone app will update the status to RainMaker cloud if `RMaker.updateAndReportParam()` API is called and print the status on Serial monitor.

### Output
```
[I][RMaker.cpp:26] event_handler(): RainMaker Initialised.
[I][WiFiProv.cpp:174] beginProvision(): Aleardy Provisioned
[I][WiFiProv.cpp:178] beginProvision(): Attempting connect to AP: Wce*****

Received value = true for Fan - power
Received value = 5 for Fan - speed
Received value = 2 for Fan - speed

[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Fan, Param Name : speed, Val : 3
[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Fan, Param Name : speed, Val : 4
[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Fan, Param Name : speed, Val : 5
[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Fan, Param Name : speed, Val : 0
[I][RMakerGeneric.cpp:197] updateAndReportParam(): Device : Fan, Param Name : power, Val : false
[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Fan, Param Name : speed, Val : 1
[I][RMakerGeneric.cpp:197] updateAndReportParam(): Device : Fan, Param Name : power, Val : true

```

