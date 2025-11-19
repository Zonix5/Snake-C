#include <Arduino.h>
extern "C" {
  #include "debugLogging.h"
}

void print(const char *msg) {
  Serial.println(msg);
}

void printInt(int var){
  Serial.println(var);
}