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
  return -1.0;  // TODO(KnowTheBird): Process Data
}

float ExampleSensor::LogAsCsv(GlucometerLogger* logger) {
  char csv_header[] =
    "Micros,Pin_State,R_Vis_Value,R_940_Value,T_Vis_Value,T_940_Value\r\n";
  logger->BlockingWrite(csv_header);

  digitalWrite(k_led_940_pin_, LOW);
  digitalWrite(k_led_617_pin_, LOW);
  delay(k_transient_delay_time_ms_);
  ReadToCsv(logger, 0);
  digitalWrite(k_led_940_pin_, HIGH);
  delay(k_transient_delay_time_ms_);
  ReadToCsv(logger, 1);
  digitalWrite(k_led_617_pin_, HIGH);
  delay(k_transient_delay_time_ms_);
  ReadToCsv(logger, 3);
  digitalWrite(k_led_940_pin_, LOW);
  delay(k_transient_delay_time_ms_);
  ReadToCsv(logger, 2);
  digitalWrite(k_led_617_pin_, LOW);
  return -1.0;  // TODO(KnowTheBird): Process Data
}

float ExampleSensor::LogAsSerial(HardwareSerial* serial_ptr) {
  digitalWrite(k_led_617_pin_, LOW);
  digitalWrite(k_led_940_pin_, LOW);
  delay(k_transient_delay_time_ms_);
  ReadToSerial(serial_ptr, 0);
  digitalWrite(k_led_940_pin_, HIGH);
  delay(k_transient_delay_time_ms_);
  ReadToSerial(serial_ptr, 1);
  digitalWrite(k_led_617_pin_, HIGH);
  delay(k_transient_delay_time_ms_);
  ReadToSerial(serial_ptr, 3);
  digitalWrite(k_led_940_pin_, LOW);
  delay(k_transient_delay_time_ms_);
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
  uint32_t last_read_time = micros();
  uint16_t index = 0;
  uint8_t logs[k_max_buff_size_];

  while ((index + k_bin_log_size_) <= k_max_buff_size_) {
    if ((micros() - last_read_time) >= 3333) {
      logs[index] = pin_states;
      last_read_time = micros();
      ReadInputs();
      logs[index + 1] = (last_read_time >> 24) & 0xff;
      logs[index + 2] = (last_read_time >> 16) & 0xff;
      logs[index + 3] = (last_read_time >> 8) & 0xff;
      logs[index + 4] = last_read_time & 0xff;
      logs[index + 5] = (PT_R_Vis_Value_ >> 4) & 0xff;
      logs[index + 6] = (PT_R_Vis_Value_ << 4) & 0xff;
      logs[index + 6] = (logs[index + 6] | (PT_R_940_Value_ >> 8)) & 0xff;
      logs[index + 7] = PT_R_940_Value_ & 0xff;
      logs[index + 8] = (PT_T_Vis_Value_ >> 4) & 0xff;
      logs[index + 9] = (PT_T_Vis_Value_ << 4) & 0xff;
      logs[index + 9] = (logs[index + 9] | (PT_T_940_Value_ >> 8)) & 0xff;
      logs[index + 10] = PT_T_940_Value_ & 0xff;
      logs[index + 11] = Compute_CRC8(logs + index, 11, crc_table_);
      index += k_bin_log_size_;
    }
  }
  logger->BlockingWrite(logs, index);
}

void ExampleSensor::ReadToCsv(GlucometerLogger* logger, uint8_t pin_states) {
  uint32_t last_read_time = micros();
  uint16_t index = 0;
  uint8_t logs[k_max_buff_size_];

  while ((index + k_bin_log_size_) <= k_max_buff_size_) {
    if ((micros() - last_read_time) >= 3333) {
      logs[index] = pin_states;
      last_read_time = micros();
      ReadInputs();
      logs[index + 1] = (last_read_time >> 24) & 0xff;
      logs[index + 2] = (last_read_time >> 16) & 0xff;
      logs[index + 3] = (last_read_time >> 8) & 0xff;
      logs[index + 4] = last_read_time & 0xff;
      logs[index + 5] = (PT_R_Vis_Value_ >> 4) & 0xff;
      logs[index + 6] = (PT_R_Vis_Value_ << 4) & 0xff;
      logs[index + 6] = (logs[index + 6] | (PT_R_940_Value_ >> 8)) & 0xff;
      logs[index + 7] = PT_R_940_Value_ & 0xff;
      logs[index + 8] = (PT_T_Vis_Value_ >> 4) & 0xff;
      logs[index + 9] = (PT_T_Vis_Value_ << 4) & 0xff;
      logs[index + 9] = (logs[index + 9] | (PT_T_940_Value_ >> 8)) & 0xff;
      logs[index + 10] = PT_T_940_Value_ & 0xff;
      logs[index + 11] = Compute_CRC8(logs + index, 11, crc_table_);
      index += k_bin_log_size_;
    }
  }

  char log_text[50];
  for (uint16_t i = 0; (i + k_bin_log_size_) <= index; i += k_bin_log_size_) {
    last_read_time =  (logs[i+1] << 24) & 0xFF000000;
    last_read_time |= (logs[i+2] << 16) & 0x00FF0000;
    last_read_time |= (logs[i+3] << 8)  & 0x0000FF00;
    last_read_time |=  logs[i+4]        & 0x000000FF;

    PT_R_Vis_Value_ =  (logs[i+5] << 4) & 0b0000111111110000;
    PT_R_Vis_Value_ |= (logs[i+6] >> 4) & 0b0000000000001111;

    PT_R_940_Value_ =  (logs[i+6] << 8) & 0b0000111100000000;
    PT_R_940_Value_ |=  logs[i+7]       & 0b0000000011111111;

    PT_T_Vis_Value_ =  (logs[i+8] << 4) & 0b0000111111110000;
    PT_T_Vis_Value_ |= (logs[i+9] >> 4) & 0b0000000000001111;

    PT_T_940_Value_ =  (logs[i+9] << 8) & 0b0000111100000000;
    PT_T_940_Value_ |=  logs[i+10]      & 0b0000000011111111;

    snprintf(log_text, sizeof(log_text), "%d,%d,%d,%d,%d,%d\r\n",
    last_read_time, logs[i], PT_R_Vis_Value_, PT_R_940_Value_,
    PT_T_Vis_Value_, PT_T_940_Value_);

    logger->Print(log_text);
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
