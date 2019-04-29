void setup() {
  pinMode(A2, INPUT);
  pinMode(A3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(A3, HIGH);
  delayMicroseconds(10);
  digitalWrite(A3, LOW);
  int t = micros();
  while (digitalRead(A2) == LOW)
    /* PASS */Serial.println("NJET");

    
  Serial.println(micros() - t);

  delay(1000);
  Serial.println("\n\nNEXT");
}
