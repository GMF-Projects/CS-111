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

const unsigned long STEP_DELAY_US = 2800;
const unsigned long EN_TIMEOUT_MS = 2000;

unsigned long lastStepTime = 0;

unsigned long lastM1Activity = 0;
unsigned long lastM2Activity = 0;
unsigned long lastM3Activity = 0;
unsigned long lastM4Activity = 0;
unsigned long lastM5Activity = 0;
unsigned long lastM6Activity = 0;

bool stepStateM1 = LOW;
bool stepStateM2 = LOW;
bool stepStateM3 = LOW;
bool stepStateM4 = LOW;
bool stepStateM5 = LOW;
bool stepStateM6 = LOW;

char cmdM1 = 'S';
char cmdM2 = 'T';
char cmdM3 = 'U';
char cmdM4 = 'V';
char cmdM5 = 'W';
char cmdM6 = 'X';

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

    Serial.print("Received: ");
    Serial.println(c);

    if (c == 'A' || c == 'B' || c == 'S') cmdM1 = c;
    if (c == 'C' || c == 'D' || c == 'T') cmdM2 = c;
    if (c == 'E' || c == 'F' || c == 'U') cmdM3 = c;
    if (c == 'G' || c == 'H' || c == 'V') cmdM4 = c;
    if (c == 'I' || c == 'J' || c == 'W') cmdM5 = c;
    if (c == 'K' || c == 'L' || c == 'X') cmdM6 = c;
  }

  // ===== MOTOR 1 =====
  if (cmdM1 == 'A' || cmdM1 == 'B') {
    digitalWrite(enPinM1, LOW);
    digitalWrite(dirPinM1, cmdM1 == 'A');
    lastM1Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM1 = !stepStateM1;
      digitalWrite(stepPinM1, stepStateM1);
    }
  } else {
    digitalWrite(stepPinM1, LOW);
    if (nowMillis - lastM1Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM1, HIGH);
  }

  // ===== MOTOR 2 =====
  if (cmdM2 == 'C' || cmdM2 == 'D') {
    digitalWrite(enPinM2, LOW);
    digitalWrite(dirPinM2, cmdM2 == 'C');
    lastM2Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM2 = !stepStateM2;
      digitalWrite(stepPinM2, stepStateM2);
    }
  } else {
    digitalWrite(stepPinM2, LOW);
    if (nowMillis - lastM2Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM2, HIGH);
  }

  // ===== MOTOR 3 =====
  if (cmdM3 == 'E' || cmdM3 == 'F') {
    digitalWrite(enPinM3, LOW);
    digitalWrite(dirPinM3, cmdM3 == 'E');
    lastM3Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM3 = !stepStateM3;
      digitalWrite(stepPinM3, stepStateM3);
    }
  } else {
    digitalWrite(stepPinM3, LOW);
    if (nowMillis - lastM3Activity >= EN_TIMEOUT_MS) digitalWrite(enPinM3, HIGH);
  }

  // ===== MOTOR 4 =====
  if (cmdM4 == 'G' || cmdM4 == 'H') {
    digitalWrite(enPinM456, LOW);
    digitalWrite(dirPinM4, cmdM4 == 'G');
    lastM4Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM4 = !stepStateM4;
      digitalWrite(stepPinM4, stepStateM4);
    }
  } else digitalWrite(stepPinM4, LOW);

  // ===== MOTOR 5 =====
  if (cmdM5 == 'I' || cmdM5 == 'J') {
    digitalWrite(enPinM456, LOW);
    digitalWrite(dirPinM5, cmdM5 == 'I');
    lastM5Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM5 = !stepStateM5;
      digitalWrite(stepPinM5, stepStateM5);
    }
  } else digitalWrite(stepPinM5, LOW);

  // ===== MOTOR 6 =====
  if (cmdM6 == 'K' || cmdM6 == 'L') {
    digitalWrite(enPinM456, LOW);
    digitalWrite(dirPinM6, cmdM6 == 'K');
    lastM6Activity = nowMillis;
    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM6 = !stepStateM6;
      digitalWrite(stepPinM6, stepStateM6);
    }
  } else digitalWrite(stepPinM6, LOW);

  if ((nowMillis-lastM4Activity >= EN_TIMEOUT_MS) &&
      (nowMillis-lastM5Activity >= EN_TIMEOUT_MS) &&
      (nowMillis-lastM6Activity >= EN_TIMEOUT_MS)) {
    digitalWrite(enPinM456, HIGH);
  }

  if (nowMicros - lastStepTime >= STEP_DELAY_US) {
    lastStepTime = nowMicros;
  }
}
