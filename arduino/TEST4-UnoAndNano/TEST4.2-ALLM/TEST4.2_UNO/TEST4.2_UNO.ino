void setup() {
  pinMode(2, INPUT_PULLUP);   // M1 CW
  pinMode(3, INPUT_PULLUP);   // M1 CCW
  pinMode(4, INPUT_PULLUP);   // M2 CW
  pinMode(5, INPUT_PULLUP);   // M2 CCW
  pinMode(6, INPUT_PULLUP);   // M3 CW
  pinMode(7, INPUT_PULLUP);   // M3 CCW

  pinMode(8, INPUT_PULLUP);   // M4 CW
  pinMode(9, INPUT_PULLUP);   // M4 CCW
  pinMode(10, INPUT_PULLUP);  // M5 CW
  pinMode(11, INPUT_PULLUP);  // M5 CCW
  pinMode(12, INPUT_PULLUP);  // M6 CW
  pinMode(13, INPUT_PULLUP);  // M6 CCW

  Serial.begin(9600);
  Serial1.begin(9600);
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

  // ===== MOTOR 4 =====
  if (digitalRead(8) == LOW && digitalRead(9) == HIGH) {
    Serial1.write('G');
    Serial.println("Send: G (M4 CW)");
  }
  else if (digitalRead(9) == LOW && digitalRead(8) == HIGH) {
    Serial1.write('H');
    Serial.println("Send: H (M4 CCW)");
  }
  else {
    Serial1.write('V');
    Serial.println("Send: V (M4 STOP)");
  }

  // ===== MOTOR 5 =====
  if (digitalRead(10) == LOW && digitalRead(11) == HIGH) {
    Serial1.write('I');
    Serial.println("Send: I (M5 CW)");
  }
  else if (digitalRead(11) == LOW && digitalRead(10) == HIGH) {
    Serial1.write('J');
    Serial.println("Send: J (M5 CCW)");
  }
  else {
    Serial1.write('W');
    Serial.println("Send: W (M5 STOP)");
  }

  // ===== MOTOR 6 =====
  if (digitalRead(12) == LOW && digitalRead(13) == HIGH) {
    Serial1.write('K');
    Serial.println("Send: K (M6 CW)");
  }
  else if (digitalRead(13) == LOW && digitalRead(12) == HIGH) {
    Serial1.write('L');
    Serial.println("Send: L (M6 CCW)");
  }
  else {
    Serial1.write('X');
    Serial.println("Send: X (M6 STOP)");
  }

  delay(200);
}
