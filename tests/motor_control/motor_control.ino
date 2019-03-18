void setup() {
  pinMode(5, OUTPUT)
  pinMode(6, OUTPUT)
  Serial.begin(9600)
}

void loop() {
  if (Serial.available()) {
    int s = Serial.parseInt();
    analogWrite(5, s);
    analogWrite(6, s);
  }
}
