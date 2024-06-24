#ifndef EXAMPLESENSOR_H_
#define EXAMPLESENSOR_H_

#include "GlucometerSensor.h"

class ExampleSensor : GlucometerSensor {
 public:
  ExampleSensor()
      : k_stage_time_us_(7000000),
        k_max_buff_size_(21600),  // 12 bytes/msg * 300 msgs/sec * 6 sec
        k_transient_delay_time_ms_(1000),
        k_bin_log_size_(12),
        k_led_617_pin_(11),
        k_led_940_pin_(12),
        k_PT_R_Vis_pin_(A1),
        k_PT_R_940_pin_(A2),
        k_PT_T_Vis_pin_(A3),
        k_PT_T_940_pin_(A4),
        GlucometerSensor() {}

  uint8_t Initialize();

  uint8_t PositionSensor(GlucometerDisplay display);

  float GetConcentration_mg_dl();

  float LogAsBinary(GlucometerLogger* logger);

  float LogAsCsv(GlucometerLogger* logger);

  float LogAsSerial(HardwareSerial* serial_ptr);

  virtual ~ExampleSensor() {}

 private:
  void ReadInputs();
  void ReadToBinary(GlucometerLogger* logger, uint8_t pin_states);
  void ReadToCsv(GlucometerLogger* logger, uint8_t pin_states);
  void ReadToSerial(HardwareSerial* serial_ptr, uint8_t pin_states);

  const uint32_t k_stage_time_us_;
  const uint16_t k_max_buff_size_;
  const uint16_t k_transient_delay_time_ms_;
  const uint8_t k_bin_log_size_;
  const uint8_t k_led_617_pin_;
  const uint8_t k_led_940_pin_;
  const uint8_t k_PT_R_Vis_pin_;
  const uint8_t k_PT_R_940_pin_;
  const uint8_t k_PT_T_Vis_pin_;
  const uint8_t k_PT_T_940_pin_;

  uint16_t PT_R_Vis_Value_;
  uint16_t PT_R_940_Value_;
  uint16_t PT_T_Vis_Value_;
  uint16_t PT_T_940_Value_;
  uint8_t crc_table_[256];
};

#endif  // EXAMPLESENSOR_H_
