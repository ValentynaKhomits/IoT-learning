const int buttonPin = 7;
const int pinRed = 13;
const int pinGreen = 12;
const int pinBlue = 8;

int currentLED = -1;
int ledPins[] = {pinRed, pinGreen, pinBlue, -1};

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(pinRed, OUTPUT);
  pinMode(pinGreen, OUTPUT);
  pinMode(pinBlue, OUTPUT);
}

void loop() {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPins[currentLED], LOW);
    currentLED = (currentLED + 1) % (sizeof(ledPins) / sizeof(ledPins[0]));
    digitalWrite(ledPins[currentLED], HIGH);
    while (digitalRead(buttonPin) == LOW) {}
  }
}