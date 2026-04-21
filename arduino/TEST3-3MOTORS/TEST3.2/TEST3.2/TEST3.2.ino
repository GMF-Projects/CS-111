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
const int btnCWM3    = A4;
const int btnCCWM3   = A5;

const int enPinM1 = 11;
const int enPinM2 = 12;
const int enPinM3 = 13;

const unsigned long STEP_DELAY_US = 2200;
const unsigned long EN_TIMEOUT_MS = 2000;

unsigned long lastStepTime = 0;
unsigned long lastM1Activity = 0;
unsigned long lastM2Activity = 0;
unsigned long lastM3Activity = 0;

bool stepStateM1 = LOW;
bool stepStateM2 = LOW;
bool stepStateM3 = LOW;

void setup() {
  pinMode(stepPinM1, OUTPUT);
  pinMode(dirPinM1, OUTPUT);
  pinMode(btnCWM1, INPUT);
  pinMode(btnCCWM1, INPUT);

  pinMode(stepPinM2, OUTPUT);
  pinMode(dirPinM2, OUTPUT);
  pinMode(btnCWM2, INPUT);
  pinMode(btnCCWM2, INPUT);

  pinMode(stepPinM3, OUTPUT);
  pinMode(dirPinM3, OUTPUT);
  pinMode(btnCWM3, INPUT);
  pinMode(btnCCWM3, INPUT);

  pinMode(enPinM1, OUTPUT);
  pinMode(enPinM2, OUTPUT);
  pinMode(enPinM3, OUTPUT);

  digitalWrite(enPinM1, HIGH);
  digitalWrite(enPinM2, HIGH);
  digitalWrite(enPinM3, HIGH);

  Serial.begin(9600);
}

void loop() {
  unsigned long now = micros();

  // ===== MOTOR 1 =====
  int cw1 = digitalRead(btnCWM1);
  int ccw1 = digitalRead(btnCCWM1);
  bool m1Active = !((cw1 == HIGH && ccw1 == HIGH) || (cw1 == LOW && ccw1 == LOW));

  if (m1Active) {
    digitalWrite(enPinM1, LOW);
    lastM1Activity = millis();

    digitalWrite(dirPinM1, cw1 == HIGH ? HIGH : LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM1 = !stepStateM1;
      digitalWrite(stepPinM1, stepStateM1);
    }
  } else {
    digitalWrite(stepPinM1, LOW);
    stepStateM1 = LOW;

    if (millis() - lastM1Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM1, HIGH);
  }

  // ===== MOTOR 2 =====
  int cw2 = digitalRead(btnCWM2);
  int ccw2 = digitalRead(btnCCWM2);
  bool m2Active = !((cw2 == HIGH && ccw2 == HIGH) || (cw2 == LOW && ccw2 == LOW));

  if (m2Active) {
    digitalWrite(enPinM2, LOW);
    lastM2Activity = millis();

    digitalWrite(dirPinM2, cw2 == HIGH ? HIGH : LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM2 = !stepStateM2;
      digitalWrite(stepPinM2, stepStateM2);
    }
  } else {
    digitalWrite(stepPinM2, LOW);
    stepStateM2 = LOW;

    if (millis() - lastM2Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM2, HIGH);
  }

  // ===== MOTOR 3 =====
  int cw3 = digitalRead(btnCWM3);
  int ccw3 = digitalRead(btnCCWM3);
  bool m3Active = !((cw3 == HIGH && ccw3 == HIGH) || (cw3 == LOW && ccw3 == LOW));

  if (m3Active) {
    digitalWrite(enPinM3, LOW);
    lastM3Activity = millis();

    digitalWrite(dirPinM3, cw3 == HIGH ? HIGH : LOW);

    if (now - lastStepTime >= STEP_DELAY_US) {
      stepStateM3 = !stepStateM3;
      digitalWrite(stepPinM3, stepStateM3);
    }
  } else {
    digitalWrite(stepPinM3, LOW);
    stepStateM3 = LOW;

    if (millis() - lastM3Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM3, HIGH);
  }

  if (now - lastStepTime >= STEP_DELAY_US)
    lastStepTime = now;
}
