🖱️ Air Mouse
A wireless Air Mouse built with an ESP32 + MPU6050, allowing you to control a computer cursor by moving the ESP32 through the air.

Air Mouse V1.0 Wiring Diagram

Air Mouse — Version 1.0
ESP32 + MPU6050 + 4-button control

✨ Features
🖱️ Motion-controlled mouse cursor using the MPU6050
📡 Bluetooth Low Energy (BLE) mouse
👈 Left click
👉 Right click
⬆️ Scroll up
⬇️ Scroll down
⚙️ Gyroscope calibration at startup
🎯 Moving-average filtering to reduce cursor jitter
🔧 Adjustable sensitivity and deadzone
🧩 Components
Component	Quantity
ESP32 Dev Module (ESP-WROOM-32) / ESP32-C3 SuperMini	1
MPU6050	1
Push Buttons	4
Jumper Wires	As required
Breadboard / PCB	1
🔌 Pin Connections
ESP32 → MPU6050
ESP32	MPU6050	Function
3V3	VCC	Power
GND	GND	Ground
GPIO 22	SCL	I²C Clock
GPIO 21	SDA	I²C Data
ESP32 → Buttons
ESP32 GPIO	Button	Function
GPIO 12	Button 1	Left Click
GPIO 13	Button 2	Right Click
GPIO 14	Button 3	Scroll Up
GPIO 27	Button 4	Scroll Down
🚀 Getting Started
Install Arduino IDE and ESP32 board support.
Install the required libraries:
BleMouse
Adafruit MPU6050
Adafruit Unified Sensor
Connect the ESP32, MPU6050, and buttons according to the wiring diagram above.
Open and upload the Air Mouse firmware.
Pair the ESP32 with your PC/laptop as a Bluetooth mouse.
Move the ESP32 in the air to control the cursor.
🎮 Controls
Action	Input
Move cursor	Move ESP32
Left Click	Button 1 / GPIO 12
Right Click	Button 2 / GPIO 13
Scroll Up	Button 3 / GPIO 14
Scroll Down	Button 4 / GPIO 27
🛠️ Calibration & Tuning
Keep the ESP32 completely still during startup so the gyroscope can calibrate correctly.

For better cursor control, tune:

sensitivity
thresholdX
thresholdY
A USB connection is recommended during development and testing for stable power.

📐 Working Principle
        ESP32
          │
          ├──── BLE ────► PC / Laptop
          │
          ├──── I²C ────► MPU6050
          │                  │
          │                  └── Motion Data
          │
          └──── GPIO ────► 4 Push Buttons
                              │
                              ├── Left Click
                              ├── Right Click
                              ├── Scroll Up
                              └── Scroll Down
The MPU6050 measures motion and rotation. The ESP32 processes the sensor data, applies filtering and sensitivity/deadzone adjustments, and sends mouse HID commands to the computer over Bluetooth.

📸 Showcase
Air Mouse V1.0 — Wireless motion-controlled mouse using ESP32 and MPU6050.

👨‍💻 Author
@ajforge-dev

⭐ If you find this project useful, consider starring the repository!
