#ifndef GLUCOMETERSENSOR_H_
#define GLUCOMETERSENSOR_H_

#include "Arduino.h"
#include "GlucometerDisplay.h"
#include "GlucometerLogger.h"

class GlucometerSensor {
 public:
  GlucometerSensor() {}

  // Return 0 only if sensor successfully initialized
  virtual uint8_t Initialize() = 0;

  // Instruct the User How to Position the Sensor, Return 0 only if successful
  virtual uint8_t PositionSensor(GlucometerDisplay display) = 0;

  // Return the blood glucose level in milligrams per deciliter
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
    serial_ptr->print(millis());
    serial_ptr->print(", ");
    serial_ptr->println(concentration);
    return concentration;
  }
};

#endif  // GLUCOMETERSENSOR_H_
