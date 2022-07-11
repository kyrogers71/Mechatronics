/*
  SparkFun Inventor’s Kit
  Circuit 3B-Distance Sensor

  Control the color of an RGB LED using an ultrasonic distance sensor.

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v40
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code


  MODIFIICATIONS FOR PENALTY KICK ROBOT
  LAST MODIFIED: 7/11/22
  MODIFIED BY: Jamie Warren
  MODIFICATIONS:
    removed all code for LED control
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

float distance = 0;               //stores the distance measured by the distance sensor

void setup()
{
  Serial.begin (9600);        //set up a serial connection with the computer

  pinMode(trigPin, OUTPUT);      //the trigger pin will output pulses of electricity
  pinMode(echoPin, INPUT);       //the echo pin will measure the duration of pulses coming back from the distance sensor
  pinMode(solenoidPin, OUTPUT);  //set solenoid pin as output
  pinMode(stopPin, OUTPUT);      //set stop pin as output
  digitalWrite(stopPin, LOW);    //set default of stop pin to low so the wheels move

  samplingPeriod = round(1000000*(1.0/SAMPLING_FREQUENCY)); //Period in microseconds 
}

void loop() {

for(int i=0; i<SAMPLES; i++)
    {
        microSeconds = micros();    //Returns the number of microseconds since the Arduino board began running the current script. 
     
        vReal[i] = analogRead(0); //Reads the value from analog pin 0 (A0), quantize it and save it as a real term.
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
    Serial.println(peak);     //Print out the most dominant frequency.
    if(peak>2000 and peak<2200){
      Serial.println("2093 Detected, Manchester United is going down"); 
      digitalWrite(soundLED, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(1000);                       // wait for a second
      digitalWrite(soundLED, LOW);
    }
 
    /*Script stops here. Hardware reset required.*/
    //while (1); //do one time
    
  distance = getDistance();        //variable to store the distance measured by the sensor

  Serial.print(distance);          //print the distance that was measured
  Serial.println(" in");           //print units after the distance
  
if (distance < 3){
  digitalWrite(stopPin, HIGH);     //send signal to Mega to stop wheels
  digitalWrite(solenoidPin, HIGH); //extend the piston
  delay(1500);                     //wait 1.5 seconds with piston extended
  digitalWrite(solenoidPin, LOW);}  //close the piston
else {Serial.print("Waiting to shoot...");}

  delay(50);                       //delay 50ms between each reading
}

//------------------FUNCTIONS-------------------------------

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
