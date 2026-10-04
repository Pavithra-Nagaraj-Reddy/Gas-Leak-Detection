# Gas Leak Detection with Alert

Arduino-based Gas Leak Detection System using an MQ-series gas sensor.

## Project Overview

This project detects gas leakage using an Arduino microcontroller and an MQ-series gas sensor.

The system monitors the surrounding air and compares the sensor reading with a calibrated baseline value.

## Features

- Gas leak detection
- Sensor calibration
- Normal, slight leak and major leak detection
- LED alert
- Buzzer alert
- Serial Monitor output

## Components Used

- Arduino UNO
- MQ-series Gas Sensor
- LED
- Buzzer
- Resistor
- Breadboard
- Jumper Wires

## Detection Levels

| Condition | Deviation | Alert |
|---|---|---|
| Normal Air | Less than 10% | LED & Buzzer OFF |
| Slight Gas Leak | 10–25% | LED Blinks + Buzzer Beeps |
| Major Gas Leak | More than 25% | LED ON + Continuous Buzzer |

## Software

Arduino IDE using C/C++.

## Authors

- Punyashree LP
- Pavithra N

## Institution

CMR Institute of Technology  
Department of Artificial Intelligence and Machine Learning


## 📄 Project Report

The complete mini-project report is available here:

[View Project Report](4th%20sem%20mini%20project%20report.pdf)

## 💻 Source Code

The Arduino source code is available here:

[View Arduino Code](code/gas_leak_detection.ino)
