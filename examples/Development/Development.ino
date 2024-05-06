#include <GlucometerSensor.h>
#include <GlucometerDisplay.h>

GlucometerSensor sensor;
GlucometerDisplay display;

void setup() {
  uint8_t setup_success = 0;
  Serial.begin(9600);

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
    float reading = sensor.GetConcentration_mg_dl();
    display.PrintConcentration_mg_dl(reading);
  } else if (display.log_sd_button_.IsNewPress()) {
    display.PrintMsg("TODO: LOG DATA ON SD");
    // TODO(ME): Log Data On SD Card
  } else if (display.stream_serial_button_.IsNewPress()) {
    display.PrintMsg("STREAMING SERIAL DATA");
    while (display.stream_serial_button_.IsPressed()) {
      Serial.println(sensor.GetConcentration_mg_dl());
      delay(1);
    }
    display.PrintMsg("DONE STREAMING DATA");
  }
}
