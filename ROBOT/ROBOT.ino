#include "PIDClass.h"
#include <TINAH.h>

//CONSTANTS:
#define KNOB_1 6 //k_d
#define KNOB_2 7 //k_p

void setup() {
  int16_t knobA = analogRead(KNOB_1); //k_d
  int16_t knobB = analogRead(KNOB_2); //k_p
  PIDClass pidController(knobB/ 4, knobA/ 4);


  

}

void loop() {
  // put your main code here, to run repeatedly:
  pidController.tapeFollow();
}
