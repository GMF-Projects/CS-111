#include <SoftwareSerial.h>

SoftwareSerial link(4, 2); // RX, TX

// ===== Motors 1-3 =====
const int stepPinM1 = 10;
const int dirPinM1  = 9;
const int enPinM1   = 11;

const int stepPinM2 = 8;
const int dirPinM2  = 7;
const int enPinM2   = 12;

const int stepPinM3 = 6;
const int dirPinM3  = 5;
const int enPinM3   = 13;

// ===== Motors 4-6 =====
const int stepPinM4 = A0;
const int dirPinM4  = A1;

const int stepPinM5 = A2;
const int dirPinM5  = A3;

const int stepPinM6 = A4;
const int dirPinM6  = A5;

const int enPinM456 = 3;

// =====================================================
// EASY TO EDIT MOTOR SPEEDS (microseconds per toggle)
// Smaller = Faster
// Bigger  = Slower
// =====================================================
const unsigned long STEP_DELAY_M1  = 2100;
const unsigned long STEP_DELAY_M2  = 2300;
const unsigned long STEP_DELAY_M3  = 2300;
const unsigned long STEP_DELAY_M45 = 2100;
const unsigned long STEP_DELAY_M6  = 3100;

const unsigned long EN_TIMEOUT_MS = 2000;

const bool DEBUG = true;

// Step timers
unsigned long lastStepTimeM1  = 0;
unsigned long lastStepTimeM2  = 0;
unsigned long lastStepTimeM3  = 0;
unsigned long lastStepTimeM45 = 0;
unsigned long lastStepTimeM6  = 0;

// Activity timers
unsigned long lastM1Activity = 0;
unsigned long lastM2Activity = 0;
unsigned long lastM3Activity = 0;
unsigned long lastM45Activity = 0;
unsigned long lastM6Activity = 0;

// Step states
bool stepStateM1 = LOW;
bool stepStateM2 = LOW;
bool stepStateM3 = LOW;
bool stepStateM45 = LOW;
bool stepStateM6 = LOW;

// Commands
char cmdM1 = 'S';
char cmdM2 = 'T';
char cmdM3 = 'U';
char cmdM45 = 'V';
char cmdM6 = 'X';

// Last command states for debug
char lastCmdM1 = 0;
char lastCmdM2 = 0;
char lastCmdM3 = 0;
char lastCmdM45 = 0;
char lastCmdM6 = 0;

void setup() {
  pinMode(stepPinM1, OUTPUT); pinMode(dirPinM1, OUTPUT); pinMode(enPinM1, OUTPUT);
  pinMode(stepPinM2, OUTPUT); pinMode(dirPinM2, OUTPUT); pinMode(enPinM2, OUTPUT);
  pinMode(stepPinM3, OUTPUT); pinMode(dirPinM3, OUTPUT); pinMode(enPinM3, OUTPUT);

  pinMode(stepPinM4, OUTPUT); pinMode(dirPinM4, OUTPUT);
  pinMode(stepPinM5, OUTPUT); pinMode(dirPinM5, OUTPUT);
  pinMode(stepPinM6, OUTPUT); pinMode(dirPinM6, OUTPUT);

  pinMode(enPinM456, OUTPUT);

  digitalWrite(enPinM1, HIGH);
  digitalWrite(enPinM2, HIGH);
  digitalWrite(enPinM3, HIGH);
  digitalWrite(enPinM456, HIGH);

  Serial.begin(9600);
  link.begin(9600);

  Serial.println("Nano ready");
}

void loop() {
  unsigned long nowMicros = micros();
  unsigned long nowMillis = millis();

  while (link.available()) {
    char c = link.read();

    if (DEBUG) {
      Serial.print("Received command: ");
      Serial.println(c);
    }

    if (c == 'A' || c == 'B' || c == 'S') cmdM1 = c;
    if (c == 'C' || c == 'D' || c == 'T') cmdM2 = c;
    if (c == 'E' || c == 'F' || c == 'U') cmdM3 = c;
    if (c == 'G' || c == 'H' || c == 'I' || c == 'J' || c == 'V') cmdM45 = c;
    if (c == 'K' || c == 'L' || c == 'X') cmdM6 = c;
  }

  // ===== MOTOR 1 =====
  if (cmdM1 != lastCmdM1 && DEBUG) {
    Serial.print("M1 command changed: ");
    Serial.println(cmdM1);
    lastCmdM1 = cmdM1;
  }

  if (cmdM1 == 'A' || cmdM1 == 'B') {
    digitalWrite(enPinM1, LOW);
    digitalWrite(dirPinM1, cmdM1 == 'A');
    lastM1Activity = nowMillis;

    if (nowMicros - lastStepTimeM1 >= STEP_DELAY_M1) {
      stepStateM1 = !stepStateM1;
      digitalWrite(stepPinM1, stepStateM1);
      lastStepTimeM1 = nowMicros;
    }
  } else {
    digitalWrite(stepPinM1, LOW);
    if (nowMillis - lastM1Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM1, HIGH);
  }

  // ===== MOTOR 2 =====
  if (cmdM2 != lastCmdM2 && DEBUG) {
    Serial.print("M2 command changed: ");
    Serial.println(cmdM2);
    lastCmdM2 = cmdM2;
  }

  if (cmdM2 == 'C' || cmdM2 == 'D') {
    digitalWrite(enPinM2, LOW);
    digitalWrite(dirPinM2, cmdM2 == 'C');
    lastM2Activity = nowMillis;

    if (nowMicros - lastStepTimeM2 >= STEP_DELAY_M2) {
      stepStateM2 = !stepStateM2;
      digitalWrite(stepPinM2, stepStateM2);
      lastStepTimeM2 = nowMicros;
    }
  } else {
    digitalWrite(stepPinM2, LOW);
    if (nowMillis - lastM2Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM2, HIGH);
  }

  // ===== MOTOR 3 =====
  if (cmdM3 != lastCmdM3 && DEBUG) {
    Serial.print("M3 command changed: ");
    Serial.println(cmdM3);
    lastCmdM3 = cmdM3;
  }

  if (cmdM3 == 'E' || cmdM3 == 'F') {
    digitalWrite(enPinM3, LOW);
    digitalWrite(dirPinM3, cmdM3 == 'E');
    lastM3Activity = nowMillis;

    if (nowMicros - lastStepTimeM3 >= STEP_DELAY_M3) {
      stepStateM3 = !stepStateM3;
      digitalWrite(stepPinM3, stepStateM3);
      lastStepTimeM3 = nowMicros;
    }
  } else {
    digitalWrite(stepPinM3, LOW);
    if (nowMillis - lastM3Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM3, HIGH);
  }

  // ===== MOTOR 4 + 5 =====
  if (cmdM45 != lastCmdM45 && DEBUG) {
    Serial.print("M4+M5 command changed: ");
    Serial.println(cmdM45);
    lastCmdM45 = cmdM45;
  }

  if (cmdM45 == 'G' || cmdM45 == 'H' || cmdM45 == 'I' || cmdM45 == 'J') {
    digitalWrite(enPinM456, LOW);

    if (cmdM45 == 'G') {
      digitalWrite(dirPinM4, HIGH);
      digitalWrite(dirPinM5, HIGH);
    } else if (cmdM45 == 'H') {
      digitalWrite(dirPinM4, LOW);
      digitalWrite(dirPinM5, LOW);
    } else if (cmdM45 == 'I') {
      digitalWrite(dirPinM4, HIGH);
      digitalWrite(dirPinM5, LOW);
    } else if (cmdM45 == 'J') {
      digitalWrite(dirPinM4, LOW);
      digitalWrite(dirPinM5, HIGH);
    }

    lastM45Activity = nowMillis;

    if (nowMicros - lastStepTimeM45 >= STEP_DELAY_M45) {
      stepStateM45 = !stepStateM45;
      digitalWrite(stepPinM4, stepStateM45);
      digitalWrite(stepPinM5, stepStateM45);
      lastStepTimeM45 = nowMicros;
    }
  } else {
    digitalWrite(stepPinM4, LOW);
    digitalWrite(stepPinM5, LOW);
  }

  // ===== MOTOR 6 =====
  if (cmdM6 != lastCmdM6 && DEBUG) {
    Serial.print("M6 command changed: ");
    Serial.println(cmdM6);
    lastCmdM6 = cmdM6;
  }

  if (cmdM6 == 'K' || cmdM6 == 'L') {
    digitalWrite(enPinM456, LOW);
    digitalWrite(dirPinM6, cmdM6 == 'K');
    lastM6Activity = nowMillis;

    if (nowMicros - lastStepTimeM6 >= STEP_DELAY_M6) {
      stepStateM6 = !stepStateM6;
      digitalWrite(stepPinM6, stepStateM6);
      lastStepTimeM6 = nowMicros;
    }
  } else {
    digitalWrite(stepPinM6, LOW);
  }

  if ((nowMillis - lastM45Activity >= EN_TIMEOUT_MS) &&
      (nowMillis - lastM6Activity >= EN_TIMEOUT_MS)) {
    digitalWrite(enPinM456, HIGH);
  }
}
