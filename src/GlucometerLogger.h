#ifndef GLUCOMETERLOGGER_H_
#define GLUCOMETERLOGGER_H_

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

class GlucometerLogger {
 public:
  GlucometerLogger() {}

  uint8_t Initialize(String* buffer) {
    buffer->reserve(1024);
    return 0;
  }

  uint8_t Begin(const int chipSelect = 4) {
    return SD.begin(chipSelect);
  }

  uint8_t Open() {
    txtFile_ = SD.open(filename_, FILE_WRITE);
    return txtFile_;
  }

  void NonBlockingWrite(String* buffer) {
    unsigned int chunkSize = txtFile_.availableForWrite();
    if (chunkSize && buffer->length() >= chunkSize) {
        txtFile_.write(buffer->c_str(), chunkSize);
        buffer->remove(0, chunkSize);
    }
  }

  void BlockingWrite(String* buffer) {
    txtFile_.write(buffer->c_str(), buffer->length());
    buffer->remove(0, buffer->length());
    txtFile_.flush();
  }

 private:
  const char filename_[9] = "data.log";
  File txtFile_;
};

#endif  // GLUCOMETERLOGGER_H_