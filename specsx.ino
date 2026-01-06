#include <Mouse.h>
#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

float gx = 0;
float gy = 0;

int vx, vy;

int blink_pin = 9;

int count = 0;

void setup()
{
  Serial.begin(9600);
  pinMode(blink_pin, INPUT);

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
  mpu.calibrateGyro();
  mpu.setThreshold(3);
}

void loop()
{
  Vector norm = mpu.readNormalizeGyro();
  int blink_state = digitalRead(blink_pin);

  Serial.println(blink_state);

  gy = norm.YAxis;
  gx = norm.XAxis;

  vx = (gx / 3);
  vy = (gy / 4);

  Mouse.move(vx, vy);

  if (blink_state == 1) {
    count = count + 10;
  }


  if (count == 2000) {
    Mouse.click(MOUSE_RIGHT);
    count = 0;
  }

  else if (( count > 1000 && count < 2000) && (blink_state == 0)) {
    Mouse.click(MOUSE_LEFT);
    count = 0;
  }
  else if (( count > 200 && count < 1000) && (blink_state == 0)) {
    count = 0;
  }

  delay(10);
}
