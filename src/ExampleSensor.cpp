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

uint8_t ExampleSensor::PositionSensor(GlucometerDisplay display) {
  display.PrintMsg("TODO: Make sure finger is detected...");
  return 0;
}

float ExampleSensor::GetConcentration_mg_dl() { return -1.0; }

float ExampleSensor::GetConcentration_mg_dl(GlucometerLogger* logger) {
  ReadInputs(logger, 0);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadInputs(logger, 1);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadInputs(logger, 2);
  digitalWrite(k_led_617_pin_, LOW);
  ReadInputs(logger, 3);
  digitalWrite(k_led_940_pin_, LOW);
  ReadInputs(logger, 0);

  return -1.0;
}

float ExampleSensor::GetConcentration_mg_dl(HardwareSerial* serial_ptr) {
  ReadInputs(serial_ptr, 0);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadInputs(serial_ptr, 1);
  //digitalWrite(k_led_940_pin_, HIGH);
  ReadInputs(serial_ptr, 2);
  //digitalWrite(k_led_617_pin_, LOW);
  ReadInputs(serial_ptr, 3);
  //digitalWrite(k_led_940_pin_, LOW);
  ReadInputs(serial_ptr, 0);

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
  delay(2);
}

void ExampleSensor::ReadInputs(GlucometerLogger* logger, uint8_t pin_states) {
  const unsigned long stage_time = 5000;
  unsigned long start_time = millis();

  while ((millis() - start_time) < stage_time) {
    ReadInputs();
    buffer_ += pin_states;
    buffer_ += ",";
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
}

void ExampleSensor::ReadInputs(HardwareSerial* serial_ptr, uint8_t pin_states) {
  const unsigned long stage_time = 5000;
  unsigned long start_time = millis();

  while ((millis() - start_time) < stage_time) {
    ReadInputs();
    // Serial.print(pin_states);
    // Serial.print(",");
    // Serial.print(PT_R_Vis_Value_);
    // Serial.print(",");
    // Serial.print(PT_R_940_Value_);
    // Serial.print(",");
    // Serial.print(PT_T_Vis_Value_);
    // Serial.print(",");
    // Serial.println(PT_T_940_Value_);

    Serial.println(PT_T_940_Value_);
  }
}