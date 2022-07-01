/*
  SparkFun Inventor’s Kit
  Circuit 5A - Motor Basics

  Learn how to control one motor with the motor driver.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code

  2022-6-20 edited for Mechatronics tape following lab

*/

//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;           //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;            //control pin 2 on the motor driver for the right motor

const int BIN1 = 6;           //control pin 1 on the motor driver for the left motor
const int BIN2 = 5;            //control pin 2 on the motor driver for the left motor

const int PWMA = 11;            //speed control pin on the motor driver for the right motor
const int PWMB = 10;            //speed control pin on the motor driver for the left motor

int sensorPin1 = A1;
int sensorPin2 = A2;

//VARIABLES
int motorSpeedRightDefault = 50;       //motor speed, right
int motorSpeedLeftDefault = 50;       //motor speed, left
int motorSpeedLeft = 50;
int motorSpeedRight = 50;
int sensorValue1 = 0;  
int sensorValue2 = 0;
int flag=0;

void setup() {
  //WE DON'T HAVE A SWITCH pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(AIN1, HIGH);                          //set pin 1 to high
  digitalWrite(AIN2, LOW);                          //set pin 2 to low

  digitalWrite(BIN1, HIGH);                          //set pin 1 to high
  digitalWrite(BIN2, LOW);                          //set pin 2 to low


  Serial.begin(9600);                       //begin serial communication with the computer
  
}

void loop() {
    // sensor checking: we will likely want to comment this out for speed once we have checked it
    sensorValue1 = analogRead(sensorPin1);
    sensorValue2 = analogRead(sensorPin2);
    Serial.println(sensorValue1);
    Serial.println(sensorValue2);
    //delay(500);
    if (sensorValue1-sensorValue2>8)                        //if tape is detected by right sensor; THIS NEEDS TO BE CHANGED
    {
    motorSpeedLeft=0;
    motorSpeedRight=motorSpeedRightDefault;
    Serial.println("Turning Left");
   }
  else if (sensorValue2-sensorValue1>8)                         //if tape is detected by left sensor; THIS NEEDS TO BE CHANGED
  {
    motorSpeedRight=0;                         
    motorSpeedLeft=motorSpeedLeftDefault;                      
    Serial.println("Turning Right");
  }
  else                                                
  {
    motorSpeedRight=motorSpeedRightDefault;                         
    motorSpeedLeft=motorSpeedRightDefault;                         
  }
    
  analogWrite(PWMA, abs(motorSpeedRight));                 //now that tape detection is set, drive it at the entered speed
  analogWrite(PWMB, abs(motorSpeedLeft));
  Serial.println(motorSpeedRight);
  Serial.println(motorSpeedLeft);
  Serial.println(' ');

}

/********************************************************************************/
