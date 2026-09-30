/*
  BLE Air Mouse - ESP32-C3 SuperMini + MPU6050
  Libraries: NimBLE-Arduino 1.4.3, ESP32-NimBLE-Mouse (wakwak-koba),
             Adafruit MPU6050, Adafruit Unified Sensor, Adafruit BusIO
  Board: ESP32C3 Dev Module, USB CDC On Boot = Enabled

  Wiring:
    MPU6050  VCC->3V3  GND->GND  SDA->GPIO8  SCL->GPIO9
    Buttons  one leg -> GPIO, other leg -> GND
             LEFT=3  RIGHT=4  SCROLL_UP=5  SCROLL_DOWN=6
Author: ajforge-dev
*/

#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <BleMouse.h>

// ---------------- Pins ----------------
const int SDA_PIN         = 8;
const int SCL_PIN         = 9;
const int LEFT_CLICK_PIN  = 3;
const int RIGHT_CLICK_PIN = 4;
const int SCROLL_UP_PIN   = 5;
const int SCROLL_DOWN_PIN = 6;

// ---------------- Tuning ----------------
float sensitivityX = 700.0;   // pixels per radian (horizontal)
float sensitivityY = 700.0;   // pixels per radian (vertical)
float deadzone     = 0.02;    // rad/s, ignore tiny motion after calibration
bool  invertX      = true;    // flip if left/right is reversed
bool  invertY      = false;   // flip if up/down is reversed
const unsigned long SCROLL_REPEAT_MS = 100;
const unsigned long DEBOUNCE_MS      = 15;
const int CAL_SAMPLES = 300;

// ---------------- Objects ----------------
BleMouse bleMouse("AirMouse", "Ashvex", 100);
Adafruit_MPU6050 mpu;

// ---------------- State ----------------
float offY = 0, offZ = 0;             // gyro bias
float remX = 0, remY = 0;             // sub-pixel remainders
unsigned long lastMicros = 0;
unsigned long lastScroll = 0;

struct Btn {
  int pin;
  bool stable;          // debounced state (true = pressed)
  bool lastRaw;
  unsigned long changedAt;
};
Btn bLeft   = {LEFT_CLICK_PIN,  false, false, 0};
Btn bRight  = {RIGHT_CLICK_PIN, false, false, 0};
Btn bUp     = {SCROLL_UP_PIN,   false, false, 0};
Btn bDown   = {SCROLL_DOWN_PIN, false, false, 0};

bool readBtn(Btn &b) {
  bool raw = (digitalRead(b.pin) == LOW);
  if (raw != b.lastRaw) {
    b.lastRaw = raw;
    b.changedAt = millis();
  }
  if (millis() - b.changedAt >= DEBOUNCE_MS) b.stable = raw;
  return b.stable;
}

void calibrateGyro() {
  Serial.println("Calibrating gyro - keep the mouse still...");
  float sy = 0, sz = 0;
  sensors_event_t a, g, t;
  for (int i = 0; i < CAL_SAMPLES; i++) {
    mpu.getEvent(&a, &g, &t);
    sy += g.gyro.y;
    sz += g.gyro.z;
    delay(5);
  }
  offY = sy / CAL_SAMPLES;
  offZ = sz / CAL_SAMPLES;
  Serial.println("Calibration done.");
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(LEFT_CLICK_PIN,  INPUT_PULLUP);
  pinMode(RIGHT_CLICK_PIN, INPUT_PULLUP);
  pinMode(SCROLL_UP_PIN,   INPUT_PULLUP);
  pinMode(SCROLL_DOWN_PIN, INPUT_PULLUP);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  if (!mpu.begin(0x68, &Wire)) {
    Serial.println("MPU6050 not found - check wiring (SDA=8, SCL=9, VCC=3V3)");
    while (true) delay(100);
  }
  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  calibrateGyro();

  bleMouse.begin();
  lastMicros = micros();
  Serial.println("Ready. Pair 'AirMouse' from Bluetooth settings.");
}

void loop() {
  if (!bleMouse.isConnected()) {
    delay(50);
    lastMicros = micros();
    return;
  }

  // ---- time step ----
  unsigned long now = micros();
  float dt = (now - lastMicros) / 1000000.0f;
  lastMicros = now;
  if (dt <= 0 || dt > 0.1f) dt = 0.005f;

  // ---- gyro -> cursor ----
  sensors_event_t a, g, t;
  mpu.getEvent(&a, &g, &t);

  float gx = g.gyro.z - offZ;   // yaw   -> horizontal
  float gy = g.gyro.y - offY;   // pitch -> vertical

  if (fabs(gx) < deadzone) gx = 0;
  if (fabs(gy) < deadzone) gy = 0;

  if (invertX) gx = -gx;
  if (invertY) gy = -gy;

  remX += gx * dt * sensitivityX;
  remY += gy * dt * sensitivityY;

  int dx = (int)remX;
  int dy = (int)remY;
  remX -= dx;
  remY -= dy;

  dx = constrain(dx, -127, 127);
  dy = constrain(dy, -127, 127);
  if (dx != 0 || dy != 0) bleMouse.move(dx, dy);

  // ---- click buttons (press/release so drag works) ----
  bool l = readBtn(bLeft);
  bool r = readBtn(bRight);

  if (l && !bleMouse.isPressed(MOUSE_LEFT))   bleMouse.press(MOUSE_LEFT);
  if (!l && bleMouse.isPressed(MOUSE_LEFT))   bleMouse.release(MOUSE_LEFT);
  if (r && !bleMouse.isPressed(MOUSE_RIGHT))  bleMouse.press(MOUSE_RIGHT);
  if (!r && bleMouse.isPressed(MOUSE_RIGHT))  bleMouse.release(MOUSE_RIGHT);

  // ---- scroll buttons (non-blocking repeat) ----
  bool up   = readBtn(bUp);
  bool down = readBtn(bDown);
  if ((up || down) && millis() - lastScroll >= SCROLL_REPEAT_MS) {
    lastScroll = millis();
    if (up)   bleMouse.move(0, 0, 1);
    if (down) bleMouse.move(0, 0, -1);
  }

  delay(5);
}

