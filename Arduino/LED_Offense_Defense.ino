//this sketch will output states and illuminate LEDs based on offense or defense mode
//Version 2, final

const int redLED = 10;
const int greenLED = 9;
const int button = 6;
const int outputState = 2;
//define pinouts

int buttonState = 0;
int robotState = 0;

void setup() {
  Serial.begin(9600);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(button, INPUT);
  //declare LEDs as outputs, button as input
  digitalWrite(redLED, LOW);
  digitalWrite(greenLED, LOW);
  //for now let's make them both off to start, then we can change later to default offense if need be
}

void loop() {
 // read the state of the pushbutton value:;
  //Serial.print(buttonState);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
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
  Serial.print(robotState);
  if (robotState ==0){
    digitalWrite(outputState, LOW);}
  else {
    digitalWrite(outputState, HIGH);}

}
