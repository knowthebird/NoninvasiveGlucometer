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

  int Open() {
    char file_name[12];
    int log_number = GetLastLogNumber() + 1;
    if (log_number <= 999) {
      snprintf(file_name, sizeof(file_name), "%s%d%s",
               prefix_, log_number, file_type_);
      txt_file_ = SD.open(file_name, O_CREAT | O_WRITE);
    }
    return static_cast<int>(txt_file_);
  }

  void Print(char *log_text) {
    txt_file_.print(log_text);
  }

  void BlockingWrite(char *log_text) {
    txt_file_.print(log_text);
    txt_file_.flush();
  }

  void BlockingWrite(uint8_t* buffer, uint16_t buffer_length) {
    txt_file_.write(buffer, buffer_length);
    txt_file_.flush();
  }

  void Close() {
    txt_file_.flush();
    txt_file_.close();
  }

  char *GetFilename() {
    return txt_file_.name();
  }

  virtual ~GlucometerLogger() {}

 private:
  const char *prefix_ = "Log_";
  const char *file_type_ = ".csv";
  File txt_file_;


  int GetLastLogNumber() {
    File dir = SD.open("/");
    File current_file =  dir.openNextFile();
    int log_counter = 0;

    while (current_file) {
      char *current_filename = current_file.name();

      // remove file extension
      char *end = current_filename + strlen(current_filename);
      while (end > current_filename && *end != '.') {
          --end;
      }
      if (end > current_filename) {
          *end = '\0';
      }

      // ignore prefix
      char *log_number_str = current_filename + strlen(prefix_);

      // Check if newer log number
      int log_number = atoi(log_number_str);
      if (log_number > log_counter) {
        log_counter = log_number;
      }

      current_file.close();
      current_file = dir.openNextFile();
    }  // while
    return log_counter;
  }  // GetLastLogNumber
};

#endif  // GLUCOMETERLOGGER_H_