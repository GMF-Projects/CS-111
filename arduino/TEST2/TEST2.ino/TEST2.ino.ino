const int stepPin  = 10;
const int dirPin   = 9;
const int btnCW    = 2;
const int btnCCW   = 3;

const unsigned long STEP_DELAY_US = 2200; // 2000 absolute MAX (range 2000-3000) 10s ish 90drg

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

  if (cw == HIGH && ccw == LOW) {
    digitalWrite(dirPin, HIGH);
  } else if (ccw == HIGH && cw == LOW) {
    digitalWrite(dirPin, LOW);
  } else {
    // both or neither — stop
    digitalWrite(stepPin, LOW);
    stepState = LOW;
    return;
  }

  // step
  if (now - lastStepTime >= STEP_DELAY_US) {
    lastStepTime = now;
    stepState = !stepState;
    digitalWrite(stepPin, stepState);
  }
}
