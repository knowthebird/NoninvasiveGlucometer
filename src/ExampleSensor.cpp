#include "ExampleSensor.h"
// #include "RunningAverage.h"
// #include "KickFiltersRT.h"

// RunningAverage myRA(7);
// const float fs = 150;
// KickFiltersRT<float> filtersRT;

uint8_t ExampleSensor::Initialize() { return 0; }

float ExampleSensor::GetConcentration_mg_dl() { return 1.0; }

float ExampleSensor::GetConcentration_mg_dl(GlucometerLogger* logger) {
  String buffer;
  logger->Initialize(&buffer);

  float some_input = 10.0;

  buffer += millis();
  buffer += ", ";
  buffer += some_input;
  buffer += "\r\n";
  logger->NonBlockingWrite(&buffer);

  float concentration = some_input / 10.0;

  buffer += millis();
  buffer += ", ";
  buffer += concentration;
  buffer += "\r\n";
  logger->BlockingWrite(&buffer);

  return concentration;
}

float ExampleSensor::GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
  float some_input = 10.0;
  float concentration = some_input / 10.0;
  if (serial_ptr->available()) {
    serial_ptr->println(some_input);
    serial_ptr->println(concentration);
  }
  return concentration;
}