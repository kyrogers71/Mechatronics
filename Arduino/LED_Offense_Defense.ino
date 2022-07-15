//this sketch will output states and illuminate LEDs based on offense or defense mode

const int redLED = 8;
const int greenLED = 9;
const int button = 6;
//define pinouts
int buttonState = 0;

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
 // read the state of the pushbutton value:
  buttonState = digitalRead(button);
  Serial.print(buttonState);
  delay(100);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    Serial.print("HIGH");
    ++buttonState;
  }
  if (buttonState == 1){
    // turn red LED on (defense):
    digitalWrite(redLED, HIGH);
    digitalWrite(greenLED, LOW);
  } else {
    // turn green LED on (offense):
    digitalWrite(greenLED, HIGH);
    digitalWrite(redLED, LOW);
  }
}
