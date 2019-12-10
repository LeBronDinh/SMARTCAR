#include <SerialCommand.h>
#include <AFMotor.h>

// setup motor:
AF_DCMotor motor1(1, MOTOR12_64KHZ);
AF_DCMotor motor2(2, MOTOR12_64KHZ);
AF_DCMotor motor3(3, MOTOR12_64KHZ);
AF_DCMotor motor4(4, MOTOR12_64KHZ);

//direction:
const byte DIRECTION_FORWARD = 0;
const byte DIRECTION_BACKWARD = 1;
const byte DIRECTION_TURNLEFT = 3;
const byte DIRECTION_TURNRIGHT = 2;
const byte DIRECTION_NONE = 4;
byte currentDirection = 4;
SerialCommand sCmd;

void setup() {
  // put your setup code here, to run once:

  setupMotor();
  addCommand();
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  sCmd.readSerial();
}
void motorForward(){
  setMotorSpeed(255);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  currentDirection = DIRECTION_FORWARD;
}
void motorBackward(){
  setMotorSpeed(255);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  currentDirection = DIRECTION_BACKWARD;
}
void motorTurnLeft(){
  if(currentDirection == DIRECTION_FORWARD){
    motor1.setSpeed(64);
    motor2.setSpeed(64);
    motor3.setSpeed(255);
    motor4.setSpeed(255);
    
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }else{
    setMotorSpeed(154);
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
  }
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  currentDirection = DIRECTION_TURNLEFT;
}
void motorTurnRight(){
  if(currentDirection == DIRECTION_FORWARD){
    motor1.setSpeed(255);
    motor2.setSpeed(255);
    motor3.setSpeed(64);
    motor4.setSpeed(64);
    
    motor3.run(FORWARD);
    motor4.run(FORWARD);
  }else{
    setMotorSpeed(164);
    motor3.run(BACKWARD);
    motor4.run(BACKWARD);
  }
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  currentDirection = DIRECTION_TURNRIGHT;
}
void motorStop(){
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  currentDirection = DIRECTION_NONE;
}
void setMotorSpeed(byte sp){
  motor1.setSpeed(sp);
  motor2.setSpeed(sp);
  motor3.setSpeed(sp);
  motor4.setSpeed(sp);
}
void setupMotor(){
  setMotorSpeed(225);
  }
void addCommand(){
  sCmd.addCommand("w", motorForward);
  sCmd.addCommand("s", motorBackward);
  sCmd.addCommand("a", motorTurnLeft);
  sCmd.addCommand("d", motorTurnRight);
  sCmd.addCommand("p", motorStop);
  }
