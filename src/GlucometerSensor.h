#ifndef GLUCOMETERSENSOR_H_
#define GLUCOMETERSENSOR_H_

#include "Arduino.h"

class GlucometerSensor {
 public:
  void GlucometerDisplay() {}

  uint8_t Initialize();

  float GetConcentration_mg_dl();
};

#endif  // GLUCOMETERSENSOR_H_
