const int stepPin  = 10;
const int dirPin   = 9;
const int btnCW    = 2;
const int btnCCW   = 3;

const unsigned long STEP_DELAY_US = 2200;

unsigned long lastStepTime = 0;
bool          stepState    = LOW;

void setup() {
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin,  OUTPUT);
  pinMode(btnCW,   INPUT);
  pinMode(btnCCW,  INPUT);
  digitalWrite(stepPin, LOW);
  Serial.begin(9600);
}

void loop() {
  unsigned long now = micros();

  int cw  = digitalRead(btnCW);
  int ccw = digitalRead(btnCCW);

  // both pressed or neither pressed = stop
  if ((cw == HIGH && ccw == HIGH) || (cw == LOW && ccw == LOW)) {
    digitalWrite(stepPin, LOW);
    stepState = LOW;
    return;
  }

  if (cw == HIGH && ccw == LOW) {
    digitalWrite(dirPin, HIGH);
  } else if (ccw == HIGH && cw == LOW) {
    digitalWrite(dirPin, LOW);
  }

  // step
  if (now - lastStepTime >= STEP_DELAY_US) {
    lastStepTime = now;
    stepState = !stepState;
    digitalWrite(stepPin, stepState);
  }
}
