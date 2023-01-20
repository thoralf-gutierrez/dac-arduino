int gatePin = 7;
int buttonPin = 2;

// 1 is not pressed, 0 is pressed
int buttonOldState = 1;
int buttonCurrentState = 1;

// turned off
int fanState = LOW;

void setup() {
  pinMode(gatePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  digitalWrite(buttonPin, HIGH);
  Serial.begin(9600);
}

void loop() {

  buttonCurrentState = digitalRead(buttonPin);

  if (buttonCurrentState != buttonOldState) {
    if (buttonCurrentState == 0) {
      // button just got pressed
      if (fanState == HIGH){
        fanState = LOW;
      } else {
        fanState = HIGH;
      }
    }
  }

  digitalWrite(gatePin, fanState);

  buttonOldState = buttonCurrentState;

  delay(10);
}
