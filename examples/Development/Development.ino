#include <GlucometerDisplay.h>
#include <GlucometerLogger.h>
#include <GlucometerSensor.h>

GlucometerLogger logger;
GlucometerDisplay display;
GlucometerSensor sensor;

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
    display.PrintMsg("Checking For SD Card");
    
    if (logger.Begin()) {
      display.PrintMsg("SD Card Detected");
        if (!logger.Open()) {
          display.PrintMsg("SD Card Detected     Failed To Write File");
        } else {
          display.PrintMsg("SD Card Detected     Logging Data");
          String buffer;
          logger.Initialize(&buffer);
          while (display.log_sd_button_.IsPressed()) {
            buffer += millis();
            buffer += ", ";
            buffer += sensor.GetConcentration_mg_dl();
            buffer += "\r\n";
            
            logger.NonBlockingWrite(&buffer);
          }
          logger.BlockingWrite(&buffer);
          display.PrintMsg("SD Card Detected     Logging Data Complete");
        }
    } else {
      display.PrintMsg("SD Card Not Detected");
    }
  } else if (display.stream_serial_button_.IsNewPress()) {
    display.PrintMsg("Streaming Serial Data");
    while (display.stream_serial_button_.IsPressed()) {
      Serial.println(sensor.GetConcentration_mg_dl());
      delay(1);
    }
    display.PrintMsg("Done Streaming Data");
  }
}
