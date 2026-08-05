#define fanPin1 19
#define fanPin2 18
#define btn1 16
#define btn2 27

int btn_count = 0;
int btn_count2 = 0;

int speed_val = 130;
bool power_state = false;

unsigned long lastDebounceTime1 = 0;
unsigned long lastDebounceTime2 = 0;
unsigned long debounceDelay = 50;

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT_PULLUP);
  pinMode(btn2, INPUT_PULLUP);
  pinMode(fanPin1, OUTPUT);
  pinMode(fanPin2, OUTPUT);
}

void loop() {
  bool reading1 = digitalRead(btn1);
  bool reading2 = digitalRead(btn2);
  handlePowerButton(reading1);
  handleSpeedButton(reading2);
  controlMotor();

}

void handlePowerButton(bool reading) {
  static bool lastButtonState = HIGH;
  if (reading != lastButtonState) {
    lastDebounceTime1 = millis();
  }

  if ((millis() - lastDebounceTime1) > debounceDelay) {
    static bool confirmedState = HIGH;
    if (reading != confirmedState) {
      confirmedState = reading;
      if (confirmedState == LOW) {
        power_state = !power_state;
        Serial.print("Power: ");
        Serial.println(power_state);
      }
    }
  }
  lastButtonState = reading;
}

void handleSpeedButton(bool reading) {
  static bool lastButtonState2 = HIGH;
  if (reading != lastButtonState2) {
    lastDebounceTime2 = millis();
  }
  if ((millis() - lastDebounceTime2) > debounceDelay) {
    static bool confirmedState2 = HIGH;
    if (reading != confirmedState2) {
      confirmedState2 = reading;
      if (confirmedState2 == LOW && power_state) {
        btn_count2 = (btn_count2 % 3) + 1;
        switch (btn_count2) {
          case 1: speed_val = 130; break;
          case 2: speed_val = 180; break;
          case 3: speed_val = 230; break;
        }
        Serial.print("Speed: ");
        Serial.println(speed_val);
      }
    }
  }
  lastButtonState2 = reading;
}

void controlMotor() {
  if (power_state) {
    digitalWrite(fanPin1, LOW);
    analogWrite(fanPin2, speed_val);
  } else {
    digitalWrite(fanPin1, LOW);
    analogWrite(fanPin2, 0);
  }
}