#include "src\WaterSensor\WaterSensor.h"

WaterSensor water = WaterSensor();

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println(water.getWaterValue());
  delay(200);
}
