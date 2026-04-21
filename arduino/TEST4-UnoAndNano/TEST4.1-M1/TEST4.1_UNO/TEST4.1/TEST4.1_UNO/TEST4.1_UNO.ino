void setup() {
  pinMode(2, INPUT_PULLUP); // M1 CW
  pinMode(3, INPUT_PULLUP); // M1 CCW
  pinMode(4, INPUT_PULLUP); // M2 CW
  pinMode(5, INPUT_PULLUP); // M2 CCW
  pinMode(6, INPUT_PULLUP); // M3 CW
  pinMode(7, INPUT_PULLUP); // M3 CCW

  Serial.begin(9600);    // Serial Monitor
  Serial1.begin(9600);   // To Nano
}

void loop() {
  // ===== MOTOR 1 =====
  if (digitalRead(2) == LOW && digitalRead(3) == HIGH) {
    Serial1.write('A');
    Serial.println("Send: A (M1 CW)");
  }
  else if (digitalRead(3) == LOW && digitalRead(2) == HIGH) {
    Serial1.write('B');
    Serial.println("Send: B (M1 CCW)");
  }
  else {
    Serial1.write('S');
    Serial.println("Send: S (M1 STOP)");
  }

  // ===== MOTOR 2 =====
  if (digitalRead(4) == LOW && digitalRead(5) == HIGH) {
    Serial1.write('C');
    Serial.println("Send: C (M2 CW)");
  }
  else if (digitalRead(5) == LOW && digitalRead(4) == HIGH) {
    Serial1.write('D');
    Serial.println("Send: D (M2 CCW)");
  }
  else {
    Serial1.write('T');
    Serial.println("Send: T (M2 STOP)");
  }

  // ===== MOTOR 3 =====
  if (digitalRead(6) == LOW && digitalRead(7) == HIGH) {
    Serial1.write('E');
    Serial.println("Send: E (M3 CW)");
  }
  else if (digitalRead(7) == LOW && digitalRead(6) == HIGH) {
    Serial1.write('F');
    Serial.println("Send: F (M3 CCW)");
  }
  else {
    Serial1.write('U');
    Serial.println("Send: U (M3 STOP)");
  }

  delay(200);
}
