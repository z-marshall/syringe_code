#include <AccelStepper.h>




// configure pins
AccelStepper stepper(AccelStepper::DRIVER, 3, 2);


// units: mm
// options: 20mL syringe has a 19.1mm diameter, 10mL syringe has a 14.8mm diameter
const float SYRINGE_DIA = 19;


// units: mL/min
const float FLOW_RATE = 40;




// area calculations (units: mm^2)
const float SYRINGE_RAD = SYRINGE_DIA / 2;
float AREA = PI * SYRINGE_RAD * SYRINGE_RAD;










// units: mm
const int SCREW_LEAD = 8;




const int POWER_BUTTON_PIN = 8;
const int LIMIT_SWITCH_PIN = 9;




const int RED_PIN = 11;
const int GREEN_PIN = 12;
const int BLUE_PIN = 13;




// PI constant is already defined in Arduino




void setup() {
// units: steps/s
float motorSpeed = FLOW_RATE * 1000 / (AREA * 60 * 0.04);


stepper.setMaxSpeed(1000);
stepper.setSpeed(motorSpeed);




// start serial connection
Serial.begin(9600);
// configure pins 8 and 9 as inputs (for the power button and limit switch) and enable the internal pullup resistor
pinMode(POWER_BUTTON_PIN, INPUT_PULLUP);
pinMode(LIMIT_SWITCH_PIN, INPUT_PULLUP);




// configure LED pins
pinMode(RED_PIN, OUTPUT);
pinMode(GREEN_PIN, OUTPUT);
pinMode(BLUE_PIN, OUTPUT);
}




void loop() {
int powerButtonVal = digitalRead(POWER_BUTTON_PIN);
int limitSwitchVal = digitalRead(LIMIT_SWITCH_PIN);
 // if the power button is pushed and the limit switch is not, run the stepper motor
if (!powerButtonVal && !limitSwitchVal) {
  stepper.runSpeed();
}




// turn the LED red for stopped, green for going, yellow for paused
if (limitSwitchVal) {
  setColor(255, 0, 0); // red
}
else if (!powerButtonVal && !limitSwitchVal) {
  setColor(0, 255, 0); // green
}
else {
  setColor(255, 165, 0); // yellow
}
}




void setColor(int redVal, int greenVal, int blueVal) {
analogWrite(RED_PIN, redVal);
analogWrite(GREEN_PIN, greenVal);
analogWrite(BLUE_PIN, blueVal);
}





