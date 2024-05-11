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
  ReadInputs(logger);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadInputs(logger);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadInputs(logger);
  digitalWrite(k_led_617_pin_, LOW);
  ReadInputs(logger);
  digitalWrite(k_led_940_pin_, LOW);
  ReadInputs(logger);

  return -1.0;
}

float ExampleSensor::GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
  ReadInputs(serial_ptr);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadInputs(serial_ptr);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadInputs(serial_ptr);
  digitalWrite(k_led_617_pin_, LOW);
  ReadInputs(serial_ptr);
  digitalWrite(k_led_940_pin_, LOW);
  ReadInputs(serial_ptr);

  return -1.0;
}

void ExampleSensor::ReadInputs() {
  const unsigned long stage_time = 5000;
  unsigned long start_time = millis();

  while ((millis() - start_time) < stage_time) {
    PT_R_Vis_Value_ = analogRead(k_PT_R_Vis_pin_);
    delay(2);
    PT_R_940_Value_ = analogRead(k_PT_R_940_pin_);
    delay(2);
    PT_T_Vis_Value_ = analogRead(k_PT_T_Vis_pin_);
    delay(2);
    PT_T_940_Value_ = analogRead(k_PT_T_940_pin_);
  }
}

void ExampleSensor::ReadInputs(GlucometerLogger* logger) {
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
}

void ExampleSensor::ReadInputs(HardwareSerial* serial_ptr) {
  ReadInputs();

  Serial.print(PT_R_Vis_Value_);
  Serial.print(",");
  Serial.print(PT_R_940_Value_);
  Serial.print(",");
  Serial.print(PT_T_Vis_Value_);
  Serial.print(",");
  Serial.println(PT_T_940_Value_);
}