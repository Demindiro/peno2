#include "bluetooth.h"

void echo(char *data, size_t len) {
  Bluetooth::send(data, len);
  Serial.write(data, len);
}

void setPassword(char *data, size_t len) {

}


void setup() {
  Serial.begin(9600);
  Bluetooth::init();
  Bluetooth::setCallback('A', echo);
  Bluetooth::setCallback('P', setPassword);
}

void loop() {
  if (Serial.available()) {
    char b = Serial.read();
    Bluetooth::send(&b, 1);
  }
}
