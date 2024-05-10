#ifndef EXAMPLESENSOR_H_
#define EXAMPLESENSOR_H_

#include "GlucometerSensor.h"

class ExampleSensor : GlucometerSensor {
 public:
  ExampleSensor()
      : k_led_617_pin_(10),
        k_led_940_pin_(11),
        k_PT_R_Vis_pin_(A1),
        k_PT_R_940_pin_(A2),
        k_PT_T_Vis_pin_(A3),
        k_PT_T_940_pin_(A4),
        GlucometerSensor() {}

  uint8_t Initialize();

  float GetConcentration_mg_dl();

  float GetConcentration_mg_dl(GlucometerLogger* logger);

  float GetConcentration_mg_dl(HardwareSerial* serial_ptr);

 private:
  void ReadInputs();

  String buffer_;
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
};

#endif  // EXAMPLESENSOR_H_
