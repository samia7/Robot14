//MOTOR PINS  
#define LEFT_MOTOR 2
#define RIGHT_MOTOR 1

//TAPE FOLLOW READINGS
#define QRD_LEFT 0
#define QRD_RIGHT 1
#include "PIDClass.h"
#include "TINAH.h"

int thresholdSpeed = 100;
int minBlackTapeVoltage_Left = 100;
int minBlackTapeVoltage_Right = 100;


PIDClass::PIDClass(int k_p, int k_d)
{

  Serial.println("PIDcontroller initialized");
  
  _thresholdSpeed = thresholdSpeed;
  _k_p = k_p;
  _k_d = k_d;
  _left_motor = LEFT_MOTOR;
  _right_motor = RIGHT_MOTOR;
  _qrd_left = QRD_LEFT;
  _qrd_right = QRD_RIGHT;
  _minBlackTapeVoltage_Left = minBlackTapeVoltage_Left;
  _minBlackTapeVoltage_Right = minBlackTapeVoltage_Right;
  _error = 0;

  

}

void PIDClass::tapeFollow() {
  TINAH::HBridge leftMotor(_left_motor);
  TINAH::HBridge rightMotor(_right_motor);
  int lasterr = 0;
  int control = 0;
  int P, D;
  float leftSensor = analogRead(_qrd_left);
  float rightSensor = analogRead(_qrd_right);
  if (leftSensor > _minBlackTapeVoltage_Left && rightSensor > _minBlackTapeVoltage_Right) {
    _error = 0;
  }
  else if (leftSensor > _minBlackTapeVoltage_Left && rightSensor < _minBlackTapeVoltage_Right) {
    _error = -1;
  }
  else if (leftSensor < _minBlackTapeVoltage_Left && rightSensor > _minBlackTapeVoltage_Right) {
    _error = 1;
  }
  else if (leftSensor < _minBlackTapeVoltage_Left && rightSensor < _minBlackTapeVoltage_Right) {
    if (lasterr >= 0) {
      _error = 5;
    }
    else if (lasterr < 0) {
      _error = -5;
    }
  }
  P = _k_p * _error;
  D = _k_d * (_error - lasterr);
  control = P + D;

  leftMotor.setOutput(_thresholdSpeed + control);
  rightMotor.setOutput(_thresholdSpeed - control);
  //LCD.clear();
 // LCD.home();
  //LCD.setCursor(0, 0); LCD.print("Kp:") + LCD.print(_k_p) + LCD.print(" Kd:") + LCD.print(_k_d)  ;
  //LCD.setCursor(0, 1); LCD.print("e:") + LCD.print(_error) + LCD.print(" r:") + LCD.print(_thresholdSpeed - control) + LCD.print(" l:") + LCD.print(_thresholdSpeed + control);
  //LCD.setCursor(0,0); LCD.print("AL: ") + LCD.print(analogRead(analogLeft)) + LCD.print(" AR: ") + LCD.print(analogRead(analogRight));
  //LCD.setCursor(0,1); LCD.print("e:") + LCD.print(error);
  //delay(200);
  lasterr = _error;

};

