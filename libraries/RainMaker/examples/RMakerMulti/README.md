# Multi Device Example

## Compile n Flash firmware

### ESP32-S2 Board
- SelfClaiming

### ESP32 Board
- Refer README.md at [here](give link to outer readme)

## What to expect in this sketch ?

- This example just demonstrates how you can have multiple devices on the same board.
- It has 3 devices
    - Switch
    - Lightbulb 
    - Temperature Sensor
- BOOT button sets the brightness of the light to 25 (this is just to demonstrate the `my_device.updateAndReportParam()`)
> NOTE:
> - The temperature value is changed by 0.5 every minute.
> - It starts at some default value (25.0) and goes on increasing till 99.5. Then it starts reducing till it comes to 0.5. The cycle keeps repeating.
> - You can check the temperature changes in the phone app.
> - Lightbulb and Fan are dummy devices, but you can try setting the values from the phone app and see them reflect on the ESP32-S2 monitor.

### Output

```
[I][RMaker.cpp:26] event_handler(): RainMaker Initialised.
[I][WiFiProv.cpp:174] beginProvision(): Aleardy Provisioned
[I][WiFiProv.cpp:178] beginProvision(): Attempting connect to AP: Wce*****

Received value = false for Switch - power
Received value = false for Light - power
Received value = true for Light - power
Received value = 86 for Light - brightness
Received value = 17 for Light - brightness
[I][RMakerGeneric.cpp:211] updateAndReportParam(): Device : Light, Param Name : brightness, Val : 25

```
