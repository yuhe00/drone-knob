# drone-knob

Sends values on the topics:

```
drone/knob/r
drone/knob/g
drone/knob/b
```

## Hardware

- ESP32
- Some potentiometers on GPIO pins 34, 35, 36

## Prerequisites

- `platformio`

## Build and run

```
PLATFORMIO_BUILD_FLAGS='-DSSID_NAME=\"<SSID_NAME>\" -DSSID_PASS=\"<SSID_PASS>\" -DMQTT_HOST=\"<MQTT_HOST>\" -DMQTT_USERNAME=\"<MQTT_USERNAME>\" -DMQTT_PASSWORD=\"<MQTT_PASSWORD>\"' \
  platformio run
```
