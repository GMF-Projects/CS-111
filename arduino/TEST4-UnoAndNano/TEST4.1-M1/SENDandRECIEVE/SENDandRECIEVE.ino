void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
}

void loop() {
  Serial1.write('X');
  Serial.println("Sent X");
  delay(500);
}
