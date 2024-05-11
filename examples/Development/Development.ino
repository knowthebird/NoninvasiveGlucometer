#include <ExampleSensor.h>
#include <GlucometerDisplay.h>
#include <GlucometerLogger.h>

ExampleSensor sensor;
GlucometerDisplay display;
GlucometerLogger logger;

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

  while (!setup_success) {
  }
}

void loop() {
  if (display.read_button_.IsNewPress()) {
    OnReadButtonPress();
  } else if (display.log_sd_button_.IsNewPress()) {
    OnSdButtonPress();
  } else if (display.stream_serial_button_.IsNewPress()) {
    OnSerialButtonPress();
  }
}

void OnReadButtonPress() {
  display.PrintMsg("Glucometer Reading   Sensor");
  float reading = sensor.GetConcentration_mg_dl();
  display.PrintConcentration_mg_dl(reading);
}

void OnSdButtonPress() {
  display.PrintMsg("Checking For SD Card");
  if (!logger.Begin()) {
    display.PrintMsg("SD Card Not Detected");
  } else {
    display.PrintMsg("SD Card Detected");
    if (!logger.Open()) {
      display.PrintMsg("SD Card Detected     Failed To Open File");
    } else {
      display.PrintMsg("SD Card Detected     Logging Data");
      while (display.log_sd_button_.IsPressed()) {
        sensor.GetConcentration_mg_dl(&logger);
      }
      logger.Close();
      display.PrintMsg("SD Card Detected     Logging Data Complete");
    }
  }
}

void OnSerialButtonPress() {
  display.PrintMsg("Waiting To Establish Serial Connection");
    display.PrintMsg("Streaming Serial Data");
    while (display.stream_serial_button_.IsPressed()) {
      sensor.GetConcentration_mg_dl((HardwareSerial*)&Serial);
    }
    display.PrintMsg("Done Streaming Data");
}
