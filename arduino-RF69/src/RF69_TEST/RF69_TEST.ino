#include <Arduino.h>

#include "RF69_REG.h"
#include "RF69.h"

char msg [] = "OLAA";

void setup() {
 Serial.begin(9600);
 Serial.println("BEGIN!");
 initRF69();
 seTx(msg,5);
}

void loop() {

}
