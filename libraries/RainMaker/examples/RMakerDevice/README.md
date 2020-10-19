# Switch Example

## Compile n Flash firmware

### ESP32-S2 Board
- SelfClaiming + SOFTAP Provisioning

### ESP32 Board
- Assisted Claiming + BLE Provisioning

## What to expect in this sketch ?

- Switch is the dummy device.
- Toggling the power button for switch device on phone app will print the status on Serial monitor.

### Output

```
[I][RMaker.cpp:26] event_handler(): RainMaker Initialised.
[I][WiFiProv.cpp:174] beginProvision(): Aleardy Provisioned
[I][WiFiProv.cpp:178] beginProvision(): Attempting connect to AP: Wce*****

Received value = false for Switch - power
Received value = true for Switch - power
```
