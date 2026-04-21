#include <SoftwareSerial.h>

SoftwareSerial link(4, 2); // RX, TX

const int stepPinM1 = 10;
const int dirPinM1  = 9;
const int enPinM1   = 11;

const int stepPinM2 = 8;
const int dirPinM2  = 7;
const int enPinM2   = 12;

const int stepPinM3 = 6;
const int dirPinM3  = 5;
const int enPinM3   = 13;

const unsigned long STEP_DELAY_US = 2200;
const unsigned long EN_TIMEOUT_MS = 2000;

unsigned long lastStepTime = 0;
unsigned long lastM1Activity = 0;
unsigned long lastM2Activity = 0;
unsigned long lastM3Activity = 0;

bool stepStateM1 = LOW;
bool stepStateM2 = LOW;
bool stepStateM3 = LOW;

char cmdM1 = 'S';
char cmdM2 = 'T';
char cmdM3 = 'U';

void setup() {
  pinMode(stepPinM1, OUTPUT);
  pinMode(dirPinM1, OUTPUT);
  pinMode(enPinM1, OUTPUT);

  pinMode(stepPinM2, OUTPUT);
  pinMode(dirPinM2, OUTPUT);
  pinMode(enPinM2, OUTPUT);

  pinMode(stepPinM3, OUTPUT);
  pinMode(dirPinM3, OUTPUT);
  pinMode(enPinM3, OUTPUT);

  digitalWrite(enPinM1, HIGH);
  digitalWrite(enPinM2, HIGH);
  digitalWrite(enPinM3, HIGH);

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
  }

  // ===== MOTOR 1 =====
  if (cmdM1 == 'A' || cmdM1 == 'B') {
    digitalWrite(enPinM1, LOW);
    digitalWrite(dirPinM1, cmdM1 == 'A' ? HIGH : LOW);
    lastM1Activity = nowMillis;

    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM1 = !stepStateM1;
      digitalWrite(stepPinM1, stepStateM1);
    }
  } else {
    digitalWrite(stepPinM1, LOW);
    if (nowMillis - lastM1Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM1, HIGH);
  }

  // ===== MOTOR 2 =====
  if (cmdM2 == 'C' || cmdM2 == 'D') {
    digitalWrite(enPinM2, LOW);
    digitalWrite(dirPinM2, cmdM2 == 'C' ? HIGH : LOW);
    lastM2Activity = nowMillis;

    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM2 = !stepStateM2;
      digitalWrite(stepPinM2, stepStateM2);
    }
  } else {
    digitalWrite(stepPinM2, LOW);
    if (nowMillis - lastM2Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM2, HIGH);
  }

  // ===== MOTOR 3 =====
  if (cmdM3 == 'E' || cmdM3 == 'F') {
    digitalWrite(enPinM3, LOW);
    digitalWrite(dirPinM3, cmdM3 == 'E' ? HIGH : LOW);
    lastM3Activity = nowMillis;

    if (nowMicros - lastStepTime >= STEP_DELAY_US) {
      stepStateM3 = !stepStateM3;
      digitalWrite(stepPinM3, stepStateM3);
    }
  } else {
    digitalWrite(stepPinM3, LOW);
    if (nowMillis - lastM3Activity >= EN_TIMEOUT_MS)
      digitalWrite(enPinM3, HIGH);
  }

  if (nowMicros - lastStepTime >= STEP_DELAY_US) {
    lastStepTime = nowMicros;
  }
}
