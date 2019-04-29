
#define LED_PIN_RED       2
#define LED_PIN_GREEN     4
#define LED_PIN_BLUE      3

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN_RED, HIGH);
}
