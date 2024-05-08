#include "ExampleSensor.h"
// #include "RunningAverage.h"
// #include "KickFiltersRT.h"

// RunningAverage myRA(7);
// const float fs = 150;
// KickFiltersRT<float> filtersRT;

uint8_t ExampleSensor::Initialize() { 
    buffer_.reserve(1024);
    return 0; 
}

float ExampleSensor::GetConcentration_mg_dl() { return 1.0; }

float ExampleSensor::GetConcentration_mg_dl(GlucometerLogger* logger) {
  float some_input = 10.0;
  float concentration = some_input / 10.0;

  buffer_ += millis();
  buffer_ += ", ";
  buffer_ += some_input;
  buffer_ += ", ";
  buffer_ += concentration;
  buffer_ += "\r\n";
  logger->NonBlockingWrite(&buffer_);

  return concentration;
}

float ExampleSensor::GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
  float some_input = 10.0;
  float concentration = some_input / 10.0;

  serial_ptr->print(millis());
  serial_ptr->print(", ");
  serial_ptr->print(some_input);
  serial_ptr->print(", ");
  serial_ptr->println(concentration);

  return concentration;
}