#ifndef EXAMPLESENSOR_H_
#define EXAMPLESENSOR_H_

#include "GlucometerSensor.h"

class ExampleSensor : GlucometerSensor {
 public:
  ExampleSensor() : GlucometerSensor() {}

  uint8_t Initialize();

  float GetConcentration_mg_dl();

  float GetConcentration_mg_dl(GlucometerLogger* logger);

  float GetConcentration_mg_dl(HardwareSerial* serial_ptr);

 private:
  String buffer_;
};

#endif  // EXAMPLESENSOR_H_
