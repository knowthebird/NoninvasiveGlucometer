#ifndef GLUCOMETERDISPLAY_H_
#define GLUCOMETERDISPLAY_H_

#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <SPI.h>
#include <Wire.h>

#define kBUTTON_A 9
#define kBUTTON_B 6
#define kBUTTON_C 5

class Button {
 public:
  Button(const uint8_t k_button_pin,
         const uint8_t k_button_mode = INPUT,
         const unsigned long k_debounce_delay_ms = 60)
      : k_button_pin_(k_button_pin),
        k_button_mode_(k_button_mode),
        k_debounce_delay_ms_(k_debounce_delay_ms),
        last_button_state_(0),
        last_debounce_time_ms_(0) {}

  void Initialize() { pinMode(k_button_pin_, k_button_mode_); }

  uint8_t IsPressed() {
    uint8_t reading = digitalRead(k_button_pin_);

    if (k_button_mode_ == INPUT_PULLUP) {
      reading = !reading;
    }

    if (reading != last_button_state_) {
      last_debounce_time_ms_ = millis();
    }

    if ((millis() - last_debounce_time_ms_) > k_debounce_delay_ms_) {
      button_state_ = reading;
    }

    last_button_state_ = reading;
    return button_state_;
  }

  uint8_t IsNewPress() {
    uint8_t prev_state = button_state_;
    IsPressed();
    return ((prev_state != button_state_) && (button_state_));
  }

  virtual ~Button() {}

 private:
  const uint8_t k_button_pin_;
  const uint8_t k_button_mode_;
  const unsigned long k_debounce_delay_ms_;  // the debounce time; increase if
                                             // the output flickers
  uint8_t button_state_;       // the current reading from the input pin
  uint8_t last_button_state_;  // the previous reading from the input pin
  unsigned long
      last_debounce_time_ms_;  // the last time the output pin was toggled
};

class GlucometerDisplay {
 public:
  GlucometerDisplay()
      : read_button_(kBUTTON_A, INPUT_PULLUP),
        log_sd_button_(kBUTTON_B, INPUT_PULLUP),
        stream_serial_button_(kBUTTON_C, INPUT_PULLUP),
        display_(Adafruit_SH1107(64, 128, &Wire)) {}

  uint8_t Initialize() {
    delay(250);                  // wait for the OLED to power up
    display_.begin(0x3C, true);  // Address 0x3C default
    display_.setRotation(1);
    display_.setTextSize(1);
    display_.setTextColor(SH110X_WHITE);

    read_button_.Initialize();
    log_sd_button_.Initialize();
    stream_serial_button_.Initialize();
    return 0;
  }

  void PrintMsg(const char* msg) {
    ResetDisplay();
    display_.println(msg);
    display_.display();
  }

  void PrintConcentration_mg_dl(float reading) {
    ResetDisplay();
    display_.println("Done Reading");
    display_.print(reading);
    display_.println(" mg/dl");
    display_.print(reading / k_mg_dl_per_mmol_L_);
    display_.println(" mmol/L");
    display_.display();
  }

  virtual ~GlucometerDisplay() {}

  Button read_button_;
  Button log_sd_button_;
  Button stream_serial_button_;

 private:
  Adafruit_SH1107 display_;
  const float k_mg_dl_per_mmol_L_ = 18.0156;

  void ResetDisplay() {
    display_.clearDisplay();
    display_.setCursor(0, 0);
    display_.println("Only Use For Research");
    display_.println("Not A Medical Device");
    display_.println("");
  }
};

#endif  // GLUCOMETERDISPLAY_H_
