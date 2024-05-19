#include <ExampleSensor.h>
#include <GlucometerDisplay.h>

ExampleSensor sensor;
GlucometerDisplay display;

const unsigned long kTimeLimit_ms = 60000;

void setup() {
  uint8_t setup_success = 0;

  if (display.Initialize() == 0) {
    unsigned long start_time = millis();
    uint8_t status = sensor.Initialize();
    unsigned long end_time = millis();

    if ((end_time - start_time) <= kTimeLimit_ms) {
      if (status == 0) {
        display.PrintMsg("Glucometer: Ready");
        setup_success = 1;
      } else {
        display.PrintMsg("Error: Sensor Init");
      }
    } else {
      display.PrintMsg("Error: Sensor Timeout");
    }
  } else {
    display.PrintMsg("Error: Display Init");
  }

  while (!setup_success) {}
}

void loop() {
  if (display.read_button_.IsNewPress()) {
    display.PrintMsg("Glucometer Reading   Sensor");

    unsigned long start_time = millis();
    float reading = sensor.GetConcentration_mg_dl();
    unsigned long end_time = millis();

    if ((end_time - start_time) <= kTimeLimit_ms) {
      display.PrintConcentration_mg_dl(reading);
    } else {
      display.PrintMsg("Error: Sensor Timeout");
    }
  }
}
