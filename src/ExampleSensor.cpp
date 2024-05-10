#include "ExampleSensor.h"
// #include "RunningAverage.h"
// #include "KickFiltersRT.h"

// RunningAverage myRA(7);
// const float fs = 150;
// KickFiltersRT<float> filtersRT;

uint8_t ExampleSensor::Initialize() { 
  pinMode(k_led_617_pin_, OUTPUT);
  digitalWrite(k_led_617_pin_, LOW);

  pinMode(k_led_940_pin_, OUTPUT);
  digitalWrite(k_led_940_pin_, LOW);

  pinMode(k_PT_R_Vis_pin_, INPUT);
  pinMode(k_PT_R_940_pin_, INPUT);
  pinMode(k_PT_T_Vis_pin_, INPUT);
  pinMode(k_PT_T_940_pin_, INPUT);

  buffer_.reserve(1024);
  return 0;
}

float ExampleSensor::GetConcentration_mg_dl() { return -1.0; }

float ExampleSensor::GetConcentration_mg_dl(GlucometerLogger* logger) {
  ReadInputs();

  buffer_ += PT_R_Vis_Value_;
  buffer_ += ",";
  buffer_ += PT_R_940_Value_;
  buffer_ += ",";
  buffer_ += PT_T_Vis_Value_;
  buffer_ += ",";
  buffer_ += PT_T_940_Value_;
  buffer_ += "\r\n";
  logger->NonBlockingWrite(&buffer_);

  return -1.0;
}

float ExampleSensor::GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
  ReadInputs();

  Serial.print(PT_R_Vis_Value_);
  Serial.print(",");
  Serial.print(PT_R_940_Value_);
  Serial.print(",");
  Serial.print(PT_T_Vis_Value_);
  Serial.print(",");
  Serial.println(PT_T_940_Value_);

  return -1.0;
}

void ExampleSensor::ReadInputs() {
  PT_R_Vis_Value_ = analogRead(k_PT_R_Vis_pin_);
  delay(2);
  PT_R_940_Value_ = analogRead(k_PT_R_940_pin_);
  delay(2);
  PT_T_Vis_Value_ = analogRead(k_PT_T_Vis_pin_);
  delay(2);
  PT_T_940_Value_ = analogRead(k_PT_T_940_pin_);
}