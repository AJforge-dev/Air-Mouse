# 🖱️ Air Mouse

A wireless **Air Mouse** built with an **ESP32 + MPU6050**, allowing you to control a computer cursor by moving the ESP32 through the air.

<p align="center">
  <img src="./Circuit Diagram.png" alt="Air Mouse V1.0 Wiring Diagram" width="850">
</p>

<p align="center">
  <b>Air Mouse — Version 1.0</b><br>
  ESP32 + MPU6050 + 4-button control
</p>

---

## ✨ Features

- 🖱️ Motion-controlled mouse cursor using the MPU6050
- 📡 Bluetooth Low Energy (BLE) mouse
- 👈 Left click
- 👉 Right click
- ⬆️ Scroll up
- ⬇️ Scroll down
- ⚙️ Gyroscope calibration at startup
- 🎯 Moving-average filtering to reduce cursor jitter
- 🔧 Adjustable sensitivity and deadzone

---

## 🧩 Components Required

| Component | Quantity |
|---|---:|
| ESP32 Dev Module (ESP-WROOM-32) / ESP32-C3 SuperMini | 1 |
| MPU6050 | 1 |
| Push Buttons | 4 |
| Jumper Wires | As required |
| Breadboard / PCB | 1 |

---

## 🔌 Pin Connections

### ESP32 → MPU6050

| ESP32 Pin | MPU6050 Pin | Function |
|---|---|---|
| 3V3 | VCC | Power |
| GND | GND | Ground |
| GPIO 22 | SCL | I²C Clock |
| GPIO 21 | SDA | I²C Data |

### ESP32 → Buttons

| ESP32 GPIO | Button | Function |
|---:|---|---|
| GPIO 12 | Button 1 | Left Click |
| GPIO 13 | Button 2 | Right Click |
| GPIO 14 | Button 3 | Scroll Up |
| GPIO 27 | Button 4 | Scroll Down |

---

## 📦 Arduino Libraries Required

Install the following libraries through:

**Arduino IDE → Sketch → Include Library → Manage Libraries**

### Required Libraries

```text
BleMouse
Adafruit MPU6050
Adafruit Unified Sensor
