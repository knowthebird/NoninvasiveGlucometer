#ifndef GLUCOMETERSENSOR_H_
#define GLUCOMETERSENSOR_H_

#include "Arduino.h"
#include "GlucometerLogger.h"

class GlucometerSensor {
 public:
  GlucometerSensor() {}

  // Return 0 if successful
  virtual uint8_t Initialize() = 0;

  virtual float GetConcentration_mg_dl() = 0;

  virtual float GetConcentration_mg_dl(GlucometerLogger* logger) {
    float concentration = GetConcentration_mg_dl();
    String buffer;
    buffer.reserve(4+3+4+3);
    buffer += millis();
    buffer += ", ";
    buffer += concentration;
    buffer += "\r\n";
    logger->BlockingWrite(&buffer);
    return concentration;
  }

  virtual float GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
    float concentration = GetConcentration_mg_dl();
    if (serial_ptr->available()) {
      serial_ptr->print(millis());
      serial_ptr->print(", ");
      serial_ptr->println(concentration);
    }
    return concentration;
  }
};

#endif  // GLUCOMETERSENSOR_H_
