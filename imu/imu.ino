// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

float data[6];

void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10);  // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.println("");
  delay(100);
}

void loop() {

  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  data[0] = a.acceleration.x;
  data[1] = a.acceleration.y;
  data[2] = a.acceleration.z;
  data[3] = a.gyro.x;
  data[4] = a.gyro.y;
  data[5] = a.gyro.z;
  /* Print out the values */
  // Serial.print("AccelX:");
  // Serial.print(a.acceleration.x);
  // Serial.print(",");
  // Serial.print("AccelY:");
  // Serial.print(a.acceleration.y);
  // Serial.print(",");
  // Serial.print("AccelZ:");
  // Serial.print(a.acceleration.z);
  // Serial.print(", ");
  // Serial.print("GyroX:");
  // Serial.print(g.gyro.x);
  // Serial.print(",");
  // Serial.print("GyroY:");
  // Serial.print(g.gyro.y);
  // Serial.print(",");
  // Serial.print("GyroZ:");
  // Serial.print(g.gyro.z);
  Serial.println(data[0] );

  delay(10);
}