#include <Arduino.h>

#include "RF69_REG.h"
#include "RF69.h"


#define NODEID 1;

char msg [] = "HELLO WORLD IM HENRIQUE GAPO";

void setup() {
 Serial.begin(9600);
 Serial.println("BEGIN!");

 initRF69();
  setRx();

}

void loop(){
  getMessage();
delay(1000);
}
