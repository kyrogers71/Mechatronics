//PIN VARIABLES
//the motor will be controlled by the motor A pins on the motor driver
const int AIN1L = 42;           //control pin 1 on the motor driver for the right motor
const int AIN2L = 40;            //control pin 2 on the motor driver for the right motor
const int PWMAL = 13;            
const int BIN1L = 36;
const int BIN2L = 38;
const int PWMBL = 11;
const int AIN1R = 45;
const int AIN2R = 47;
const int PWMAR = 7;
const int BIN1R = 46;
const int BIN2R = 44;
const int PWMBR = 4;
const int Mov_pin = 2;
const int Stop_pin = 24;

//int switchPin = 7;             //switch to turn the robot on and off

//VARIABLES
int motorSpeed=255;      //starting speed for the motor
//int ch=3;
void setup() {
  //pinMode(switchPin, INPUT_PULLUP);   //set this as a pullup to sense whether the switch is flipped

  //set the motor control pins as outputs
  pinMode(AIN1L, OUTPUT);
  pinMode(AIN2L, OUTPUT);
  pinMode(PWMAL, OUTPUT);
  pinMode(BIN1L, OUTPUT);
  pinMode(BIN2L, OUTPUT);
  pinMode(PWMBL, OUTPUT);
  pinMode(AIN1R, OUTPUT);
  pinMode(AIN2R, OUTPUT);
  pinMode(PWMAR, OUTPUT);
  pinMode(BIN1R, OUTPUT);
  pinMode(BIN2R, OUTPUT);
  pinMode(PWMBR, OUTPUT);
  pinMode(Mov_pin, INPUT);
  pinMode(Stop_pin, INPUT);
 
  Serial.begin(115200);                       //begin serial communication with the computer

  //Serial.println("Enter CHOICE (1,2,-1)... ");    //Prompt to get input in the serial monitor.
}

void loop() {

  //spinMotor();

   if(digitalRead(Mov_pin) == HIGH && digitalRead(Stop_pin) == LOW )
   {
   digitalWrite(AIN1L, HIGH);                         //set pin 1 to high
   digitalWrite(AIN2L, LOW);                          //set pin 2 to low
   digitalWrite(BIN1L, HIGH);                        
   digitalWrite(BIN2L, LOW);
   digitalWrite(AIN1R, HIGH);
   digitalWrite(AIN2R, LOW);
   digitalWrite(BIN1R, HIGH);
   digitalWrite(BIN2R, LOW);
   analogWrite(PWMAL, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
   analogWrite(PWMBL, abs(motorSpeed));  
   analogWrite(PWMAR, abs(motorSpeed));
   analogWrite(PWMBR, abs(motorSpeed));
   Serial.println(" PIN 2 IS ON ");
   }
   
   if(digitalRead(Stop_pin) == HIGH)
   {
    delay(200);                                       //wait for piston to deploy, then stop the robot
    digitalWrite(AIN1L, HIGH);                         //set pin 1 to high
   digitalWrite(AIN2L, LOW);                          //set pin 2 to low
   digitalWrite(BIN1L, HIGH);                        
   digitalWrite(BIN2L, LOW);
   digitalWrite(AIN1R, HIGH);
   digitalWrite(AIN2R, LOW);
   digitalWrite(BIN1R, HIGH);
   digitalWrite(BIN2R, LOW);
   analogWrite(PWMAL, 0);                 //now that the motor direction is set, drive it at the entered speed
   analogWrite(PWMBL, 0);  
   analogWrite(PWMAR, 0);
   analogWrite(PWMBR, 0);
   Serial.println(" STOP IT! ");
   do_nothing();
   }
   if(digitalRead(Mov_pin) == LOW){
   
   digitalWrite(AIN1L, HIGH);                         //set pin 1 to high
   digitalWrite(AIN2L, LOW);                          //set pin 2 to low
   digitalWrite(BIN1L, HIGH);                        
   digitalWrite(BIN2L, LOW);
   digitalWrite(AIN1R, HIGH);
   digitalWrite(AIN2R, LOW);
   digitalWrite(BIN1R, HIGH);
   digitalWrite(BIN2R, LOW);
   analogWrite(PWMAL, 0);                 //now that the motor direction is set, drive it at the entered speed
   analogWrite(PWMBL, 0);  
   analogWrite(PWMAR, 0);
   analogWrite(PWMBR, 0);
    Serial.println(" PIN 2 IS OFF ");
   }
   
   /*if(digitalRead(Stop_pin) == LOW){
    Serial.println(" NO STOP!! ");
   }
   /*digitalWrite(AIN1L, LOW);                         //set pin 1 to high
   digitalWrite(AIN2L, HIGH);                          //set pin 2 to low
   digitalWrite(BIN1L, LOW);                        
   digitalWrite(BIN2L, HIGH);
   digitalWrite(AIN1R, LOW);
   digitalWrite(AIN2R, HIGH);
   digitalWrite(BIN1R, LOW);
   digitalWrite(BIN2R, HIGH);
   analogWrite(PWMAL, abs(motorSpeed));                 //now that the motor direction is set, drive it at the entered speed
   analogWrite(PWMBL, abs(motorSpeed));  
   analogWrite(PWMAR, abs(motorSpeed));
   analogWrite(PWMBR, abs(motorSpeed));
   delay(3000);*/
}

/********************************************************************************/
void do_nothing()                       //function for driving the right motor
{
   Serial.println("Do nothing!");
}
