#include <GlucometerSensor.h>
#include <GlucometerDisplay.h>

GlucometerSensor sensor;
GlucometerDisplay display;

const unsigned long kTimeLimit_ms = 5000;

void setup() {
  uint8_t setup_success = 0;

  if (display.Initialize() == 0) {
    if (sensor.Initialize() == 0) {
      display.PrintMsg("Glucometer: Ready");
      setup_success = 1;
    } else {
      display.PrintMsg("Error: Sensor Init");
    }
  } else {
    display.PrintMsg("Error: Display Init");
  }

  while (!setup_success) {}
}

void loop() {
  if (display.read_button_.IsNewPress()) {
    display.PrintMsg("Glucometer Reading   Sensor");

    const unsigned long start_time = millis();
    float reading = sensor.GetConcentration_mg_dl();
    const unsigned long end_time = millis();

    if ((end_time - start_time) <= kTimeLimit_ms) {
      display.PrintConcentration_mg_dl(reading);
    } else {
      display.PrintMsg("Error: Sensor Timeout");
    }
  }
}
