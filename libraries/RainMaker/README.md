# ESP RainMaker library for Arduino
The Arduino IDE provides an excellent library for working with ESP RainMaker.
ESP RainMaker is an end-to-end solution offered by Espressif to enable remote control and monitoring for ESP32-S2 and ESP32 based products without any configuration required in the Cloud.
The primary components of this solution are:
- Claiming Service (to get the Cloud connectivity credentials)
- RainMaker library (i.e. this library, to develop the firmware)
- RainMaker Cloud (backend, offering remote connectivity)
- RainMaker Phone App/CLI (Client utilities for remote access)

The key features of ESP RainMaker are:

1. Ability to define own devices and parameters, of any type, in the firmware.
2. Zero configuration required on the Cloud.
3. Phone apps that dynamically render the UI as per the device information.

This RainMaker library is built using esp-rainmaker component.

#### Repository Source

- [ESP RainMaker](https://github.com/espressif/esp-rainmaker)

## Phone Apps

### Android

- [Google PlayStore](https://play.google.com/store/apps/details?id=com.espressif.rainmaker)
- [Direct APK](https://github.com/espressif/esp-rainmaker/wiki)
- [Source Code](https://github.com/espressif/esp-rainmaker-android)

### iOS
- [Apple App Store](https://apps.apple.com/app/esp-rainmaker/id1497491540)
- [Source Code](https://github.com/espressif/esp-rainmaker-ios)

## Documentation

Please check the ESP RainMaker documentation [here](http://rainmaker.espressif.com/docs/get-started.html) to get started.

Each example has its own README with additional information about using this library.

## Claiming

> NOTE : It is mandatory to call provisioning API according to the board specified below, since it is responsible for user-node mapping.
1. ESP32 Board - Assisted claiming + BLE Provisioning
2. ESP32S2 Board - Self Claiming + SOFTAP Provisioning
