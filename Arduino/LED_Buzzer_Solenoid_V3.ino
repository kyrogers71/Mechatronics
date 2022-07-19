/*
  SparkFun Inventor’s Kit
  Circuit 3B-Distance Sensor
  Control the color of an RGB LED using an ultrasonic distance sensor.
  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.
  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
  MODIFIICATIONS FOR PENALTY KICK ROBOT
  LAST MODIFIED: 7/13/22
  MODIFIED BY: Kyle Rogers
  MODIFICATIONS:
    added sections for sound sensor start
*/
#include "arduinoFFT.h"
 
#define SAMPLES 128             //SAMPLES-pt FFT. Must be a base 2 number. Max 128 for Arduino Uno.
#define SAMPLING_FREQUENCY 5000//Ts = Based on Nyquist, must be 2 times the highest expected frequency.
 
arduinoFFT FFT = arduinoFFT();
 
unsigned int samplingPeriod;
unsigned long microSeconds;
 
double vReal[SAMPLES]; //create vector of size SAMPLES to hold real values
double vImag[SAMPLES]; //create vector of size SAMPLES to hold imaginary values

const int soundLED = 13;          //LED to indicate that the buzzer has been heard
const int trigPin = 11;           //connects to the trigger pin on the distance sensor
const int echoPin = 12;           //connects to the echo pin on the distance sensor
const int solenoidPin = 6;        //set output pin for piston trigger
const int stopPin = 3;            //output pin to tell wheels to stop on Mega
const int soundPin = 10;           //output pin to tell Mega the buzzer sound has been heard

const int redLED = 9;
const int greenLED = 8;
const int button = 7;
const int outputState = 2;
//define pinouts for LED offense/defense switch

float distance = 0;               //stores the distance measured by the distance sensor
int soundflag = 0;              //flag for if we have heard start sound yet
int buzzer = 0;

int buttonState = 0;
int robotState = 0;
int timer = 0;                  //states for LED offense/defense


void setup()
{
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);      //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);       //the echo pin will measure the duration of pulses coming back from the distance sensor
  pinMode(solenoidPin, OUTPUT);  //set solenoid pin as output
  pinMode(stopPin, OUTPUT);      //set stop pin as output
  digitalWrite(stopPin, LOW);    //set default of stop pin to low so the wheels move
  digitalWrite(soundPin, LOW);   //set default of sound pin to low so robot sits at rest

  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds

  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  //declare LEDs as outputs, button as input
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  //for now let's make them both off to start, then we can change later to default offense if need be
}

void loop() {

  while (true){
  if (digitalRead(button) == HIGH) {
    ++buttonState;
    delay(100);
  }
  if ((buttonState & 1) == 0){
    // turn red LED on (defense):
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
    robotState = 0;
    delay(100);
  } else {
    // turn green LED on (offense):
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
    robotState = 1;
    delay(100);
  }
  //Serial.print(robotState);
  if (robotState ==0){
    digitalWrite(outputState, LOW);}
  else {
    digitalWrite(outputState, HIGH);}

  if (timer == 60){
    break;
  }
  else {++timer;
  Serial.print(timer);
  }
  }
  //Serial.print(buzzer);
  if (buzzer == 0){
    buzzer = isSoundOn();}
  if (buzzer == 1){              //comment this back in to use the sound sensor
      digitalWrite(soundLED, HIGH);       // turn the LED on (HIGH is the voltage level)
      digitalWrite(soundPin, HIGH);       // tell the Mega that the sound has been heard
}
      
  distance = getDistance();        //variable to store the distance measured by the sensor

  Serial.print(distance);          //print the distance that was measured
  Serial.println(" in");           //print units after the distance
  
if (distance < 3 && buzzer ==1){   //<---------------SET DISTANCE FOR BALL TO SENSOR HERE------------------------
  digitalWrite(stopPin, HIGH);     //send signal to Mega to stop wheels
  digitalWrite(solenoidPin, HIGH); //extend the piston
  delay(1500);                     //wait 1.5 seconds with piston extended
  digitalWrite(solenoidPin, LOW);  //close the piston
  delay(30000);}                     //WAIT FOR 30 SECONDS TO AVOID GOING AGAIN
else {Serial.print("Waiting to shoot...");}

  delay(50);                       //delay 50ms between each reading
  //Serial.print(buzzer);
  //Serial.print("    ");
}

//------------------FUNCTIONS-------------------------------

int isSoundOn(){

for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();          //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(0);         //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
        vImag[i] = 0; //Makes imaginary term 0 always

        /*remaining wait time between samples if necessary*/
        while(micros() < (microSeconds + samplingPeriod))
        {
          //do nothing
        }
    }
 
    /*Perform FFT on samples*/
    FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
    FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
    FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

    /*Find peak frequency and print peak*/
    double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);
    //Serial.println(peak);                 //Print out the most dominant frequency.
    if(peak>2000 and peak<2200){
      soundflag = 1;
      Serial.println("2093 Detected, Manchester United is going down"); 
      //Serial.println(soundflag);
      //Serial.println(" ");                      //comment back in to use the sound sensor
      }
    return soundflag;
    }

//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance()
{
  float echoTime;                   //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;         //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);      //use the pulsein command to see how long it takes for the
                                          //pulse to bounce back to the sensor

  calculatedDistance = echoTime / 148.0;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;              //send back the distance that was calculated
}
