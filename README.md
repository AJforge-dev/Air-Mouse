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
```
**🛠️ Calibration & Tuning**

### Keep the ESP32 completely still during startup so that the gyroscope can calibrate correctly.

For better cursor control, adjust:
```
sensitivity
thresholdX
thresholdY
```
These parameters can be tuned according to your preferred cursor movement and responsiveness.

A USB connection is recommended during development and testing for stable power.

**🚀 Getting Started**
1. Install Arduino IDE

Install Arduino IDE and add ESP32 board support.

2. Install Required Libraries

Install:
```
BleMouse
Adafruit MPU6050
Adafruit Unified Sensor
```
3. Connect the Hardware

Connect the ESP32, MPU6050 and four push buttons according to the wiring diagram.

4. Upload the Code

Open the Air Mouse firmware in Arduino IDE and upload it to the ESP32.

5. Pair with Your Computer

After uploading:
```
Power on the ESP32.
Open Bluetooth settings on your PC/laptop.
Search for the ESP32 Air Mouse.
Pair it as a Bluetooth mouse.
```
6. Control the Cursor

Move the ESP32 through the air to control the mouse cursor.
