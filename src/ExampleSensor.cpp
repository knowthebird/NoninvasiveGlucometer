#include "ExampleSensor.h"
#include "CRC8.h"

uint8_t ExampleSensor::Initialize() {
  analogReadResolution(12);  // For ATSAMD21G18 ARM Cortex M0
  pinMode(k_led_617_pin_, OUTPUT);
  digitalWrite(k_led_617_pin_, LOW);

  pinMode(k_led_940_pin_, OUTPUT);
  digitalWrite(k_led_940_pin_, LOW);

  pinMode(k_PT_R_Vis_pin_, INPUT);
  pinMode(k_PT_R_940_pin_, INPUT);
  pinMode(k_PT_T_Vis_pin_, INPUT);
  pinMode(k_PT_T_940_pin_, INPUT);

  buffer_.reserve(1024);
  CalculateTable_CRC8(crc_table_);
  return 0;
}

uint8_t ExampleSensor::PositionSensor(GlucometerDisplay display) {
  display.PrintMsg("TODO(KnowTheBird): Make sure finger is detected...");
  return 0;
}

float ExampleSensor::GetConcentration_mg_dl() {
  return -1.0;  // TODO(KnowTheBird): Process Data
}

float ExampleSensor::LogAsBinary(GlucometerLogger* logger) {
  digitalWrite(k_led_940_pin_, LOW);
  digitalWrite(k_led_617_pin_, LOW);
  ReadToBinary(logger, 0);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadToBinary(logger, 1);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadToBinary(logger, 3);
  digitalWrite(k_led_940_pin_, LOW);
  ReadToBinary(logger, 2);
  digitalWrite(k_led_617_pin_, LOW);
  logger->BlockingWrite(&buffer_);
  return -1.0;  // TODO(KnowTheBird): Process Data
}

float ExampleSensor::LogAsCsv(GlucometerLogger* logger) {
  buffer_ = "Micros,Pin_State,R_Vis_Value,R_940_Value,T_Vis_Value,T_940_Value\r\n";
  digitalWrite(k_led_940_pin_, LOW);
  digitalWrite(k_led_617_pin_, LOW);
  ReadToCsv(logger, 0);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadToCsv(logger, 1);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadToCsv(logger, 3);
  digitalWrite(k_led_940_pin_, LOW);
  ReadToCsv(logger, 2);
  digitalWrite(k_led_617_pin_, LOW);
  logger->BlockingWrite(&buffer_);
  return -1.0;  // TODO(KnowTheBird): Process Data
}

float ExampleSensor::LogAsSerial(HardwareSerial* serial_ptr) {
  digitalWrite(k_led_617_pin_, LOW);
  digitalWrite(k_led_940_pin_, LOW);
  ReadToSerial(serial_ptr, 0);
  digitalWrite(k_led_940_pin_, HIGH);
  ReadToSerial(serial_ptr, 1);
  digitalWrite(k_led_617_pin_, HIGH);
  ReadToSerial(serial_ptr, 3);
  digitalWrite(k_led_940_pin_, LOW);
  ReadToSerial(serial_ptr, 2);
  digitalWrite(k_led_617_pin_, LOW);

  return -1.0;  // TODO(KnowTheBird): Process Data
}

void ExampleSensor::ReadInputs() {
  PT_R_Vis_Value_ = analogRead(k_PT_R_Vis_pin_);
  PT_R_940_Value_ = analogRead(k_PT_R_940_pin_);
  PT_T_Vis_Value_ = analogRead(k_PT_T_Vis_pin_);
  PT_T_940_Value_ = analogRead(k_PT_T_940_pin_);
}

void ExampleSensor::ReadToBinary(GlucometerLogger* logger, uint8_t pin_states) {
  uint32_t start_time = micros();
  uint32_t current_time = start_time;

  while ((current_time - start_time) < k_stage_time_us_) {
    uint8_t temp_buffer[12];
    temp_buffer[0] = pin_states;

    current_time = micros();
    ReadInputs();

    temp_buffer[1] = (current_time >> 24) & 0xff;
    temp_buffer[2] = (current_time >> 16) & 0xff;
    temp_buffer[3] = (current_time >> 8) & 0xff;
    temp_buffer[4] = current_time & 0xff;

    temp_buffer[5] = (PT_R_Vis_Value_ >> 4) & 0xff;
    temp_buffer[6] = (PT_R_Vis_Value_ << 4) & 0xff;
    temp_buffer[6] = (temp_buffer[6] | (PT_R_940_Value_ >> 8)) & 0xff;
    temp_buffer[7] = PT_R_940_Value_ & 0xff;

    temp_buffer[8] = (PT_T_Vis_Value_ >> 4) & 0xff;
    temp_buffer[9] = (PT_T_Vis_Value_ << 4) & 0xff;
    temp_buffer[9] = (temp_buffer[9] | (PT_T_940_Value_ >> 8)) & 0xff;
    temp_buffer[10] = PT_T_940_Value_ & 0xff;

    temp_buffer[11] = Compute_CRC8(temp_buffer, 11, crc_table_);

    for (int i = 0; i < 12; i++) {
      buffer_ += static_cast<char>(temp_buffer[i]);
    }

    logger->NonBlockingWrite(&buffer_);
  }
}

void ExampleSensor::ReadToCsv(GlucometerLogger* logger, uint8_t pin_states) {
  uint32_t start_time = micros();
  uint32_t current_time = start_time;

  while ((current_time - start_time) < k_stage_time_us_) {
    current_time = micros();
    ReadInputs();
    buffer_ += current_time;
    buffer_ += ",";
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

void ExampleSensor::ReadToSerial(HardwareSerial* serial_ptr, uint8_t pin_states) {
  uint32_t start_time = micros();
  uint32_t current_time = start_time;

  while ((current_time - start_time) < k_stage_time_us_) {
    current_time = micros();
    ReadInputs();
    Serial.print(current_time);
    Serial.print(",");
    Serial.print(pin_states);
    Serial.print(",");
    Serial.print(PT_R_Vis_Value_);
    Serial.print(",");
    Serial.print(PT_R_940_Value_);
    Serial.print(",");
    Serial.print(PT_T_Vis_Value_);
    Serial.print(",");
    Serial.println(PT_T_940_Value_);
  }
}
