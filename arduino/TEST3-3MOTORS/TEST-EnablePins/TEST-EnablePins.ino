void setup() {
  pinMode(11, OUTPUT); // M1 EN
  pinMode(12, OUTPUT); // M2 EN
  pinMode(13, OUTPUT); // M3 EN
}

void loop() {
  // Enable all drivers
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(500);

  // Disable all drivers
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  delay(500);
}
