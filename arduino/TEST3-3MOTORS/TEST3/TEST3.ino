const int stepPinM1  = 10;
const int dirPinM1   = 9;
const int btnCWM1    = A0;
const int btnCCWM1   = A1;

const int stepPinM2  = 8;
const int dirPinM2   = 7;
const int btnCWM2    = A2;
const int btnCCWM2   = A3;

const int stepPinM3  = 6;
const int dirPinM3   = 5;
const int btnCWM3    = A4;  // FIXED
const int btnCCWM3   = A5;  // FIXED

const unsigned long STEP_DELAY_US = 2200;

unsigned long lastStepTime = 0;

bool stepStateM1 = LOW;
bool stepStateM2 = LOW;
bool stepStateM3 = LOW;

void setup() {
  pinMode(stepPinM1, OUTPUT);
  pinMode(dirPinM1,  OUTPUT);
  pinMode(btnCWM1,   INPUT);
  pinMode(btnCCWM1,  INPUT);

  pinMode(stepPinM2, OUTPUT);
  pinMode(dirPinM2,  OUTPUT);
  pinMode(btnCWM2,   INPUT);
  pinMode(btnCCWM2,  INPUT);

  pinMode(stepPinM3, OUTPUT);
  pinMode(dirPinM3,  OUTPUT);
  pinMode(btnCWM3,   INPUT);
  pinMode(btnCCWM3,  INPUT);

  digitalWrite(stepPinM1, LOW);
  digitalWrite(stepPinM2, LOW);
  digitalWrite(stepPinM3, LOW);

  Serial.begin(9600);
}

void loop() {
  unsigned long now = micros();

  // ===== MOTOR 1 =====
  int cw1  = digitalRead(btnCWM1);
  int ccw1 = digitalRead(btnCCWM1);

  if (!((cw1 == HIGH && ccw1 == HIGH) || (cw1 == LOW && ccw1 == LOW))) {
    if (cw1 == HIGH) digitalWrite(dirPinM1, HIGH);
    else digitalWrite(dirPinM1, LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM1 = !stepStateM1;
      digitalWrite(stepPinM1, stepStateM1);
    }
  } else {
    digitalWrite(stepPinM1, LOW);
    stepStateM1 = LOW;
  }

  // ===== MOTOR 2 =====
  int cw2  = digitalRead(btnCWM2);
  int ccw2 = digitalRead(btnCCWM2);

  if (!((cw2 == HIGH && ccw2 == HIGH) || (cw2 == LOW && ccw2 == LOW))) {
    if (cw2 == HIGH) digitalWrite(dirPinM2, HIGH);
    else digitalWrite(dirPinM2, LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM2 = !stepStateM2;
      digitalWrite(stepPinM2, stepStateM2);
    }
  } else {
    digitalWrite(stepPinM2, LOW);
    stepStateM2 = LOW;
  }

  // ===== MOTOR 3 =====
  int cw3  = digitalRead(btnCWM3);
  int ccw3 = digitalRead(btnCCWM3);

  if (!((cw3 == HIGH && ccw3 == HIGH) || (cw3 == LOW && ccw3 == LOW))) {
    if (cw3 == HIGH) digitalWrite(dirPinM3, HIGH);
    else digitalWrite(dirPinM3, LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM3 = !stepStateM3;
      digitalWrite(stepPinM3, stepStateM3);
    }
  } else {
    digitalWrite(stepPinM3, LOW);
    stepStateM3 = LOW;
  }

  // update shared timer
  if (now - lastStepTime >= STEP_DELAY_US) {
    lastStepTime = now;
  }
}
