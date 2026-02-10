# mGaugeESP

This software is the ESP component of mGauge.

## What is mGauge?

mGauge consists of two components connected via Bluetooth Low Energy (BLE).

## ESP32 Gauge

A measuring device with two functions, based on an ESP32-S3.

The ESP32-S3 was chosen because it supports BLE 5.0, ensuring a secure connection to the mGauge GUI.

- INA219 for measuring DC current
- Voltage: 0-26V
- Current: 0-3.2A
- Power: 0-83.2W
- 3.5" LCD display for current and voltage
- xy-FX35 as an electronic resistor

with a maximum power rating of 35W (1-25V, 0-5A)

### GUI

Qt PC software for displaying and recording measurement data

- Plotting of measured values
- Saving measured values ​​as *.csv files.

Code is available in the `mGaugeGUI` repository.

