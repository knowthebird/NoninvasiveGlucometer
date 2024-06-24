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
    char log_text[25];
    snprintf(log_text, sizeof(log_text), "%d, %6.2f\r\n", millis(), concentration);
    logger->BlockingWrite(log_text);
    return concentration;
  }

  virtual float GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
    float concentration = GetConcentration_mg_dl();
    char log_text[25];
    snprintf(log_text, sizeof(log_text), "%d, %6.2f\r\n", millis(), concentration);
    serial_ptr->print(log_text);
    return concentration;
  }

  virtual ~GlucometerSensor() {}
};

#endif  // GLUCOMETERSENSOR_H_
