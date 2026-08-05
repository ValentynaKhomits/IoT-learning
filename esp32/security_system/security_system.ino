#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "MFRC522_I2C.h"
#define pyroelectric 14
#define led_y 12  // Yellow LED pin definition
#define buzzerPin 17
LiquidCrystal_I2C mylcd(0x27, 16, 2);
MFRC522_I2C mfrc522(0x28, -1);

const String CORRECT_UID = "20214788220";
bool isLocked = true;

void setup() {
  Serial.begin(9600);
  Wire.begin(); // Стандартні піни ESP32: SDA -> GPIO21, SCL -> GPIO22
  mylcd.init();
  mylcd.backlight();
  displayMessage("System is locked", "        ");
  mfrc522.PCD_Init();
  Serial.println("System ready. Scan PICC...");
  pinMode(pyroelectric, INPUT);
  pinMode(led_y, OUTPUT);  // Set pin as output mode
  digitalWrite(led_y, HIGH);
  pinMode(buzzerPin, OUTPUT);
}
void loop() {
  boolean pyroelectric_val = digitalRead(pyroelectric);
  delay(200);

  if(pyroelectric_val == 1 && isLocked){
    // tone(buzzerPin, 440);
    Serial.println("ALARM!!!");
  }
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    delay(50);
    return;
  }
  bool cardIsValid = checkCard();
  if (cardIsValid) {
    noTone(buzzerPin);
    isLocked = !isLocked;
    if (isLocked) {
      displayMessage("System is locked", "");
      digitalWrite(led_y, HIGH);
    } else {
      displayMessage("System is open", "");
      digitalWrite(led_y, LOW);
    }
  }
  delay(2000); // Пауза перед наступним зчитуванням
}
bool checkCard () {
  String currentUID = "";
  Serial.print("Card UID: ");
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    currentUID += String(mfrc522.uid.uidByte[i]);
  }
  Serial.println(currentUID);
  // Перевірка прав доступу
  if (currentUID == CORRECT_UID) {
    Serial.println("Access Granted");
    return true;
  } else {
    Serial.println("Access Denied");
    return false;
  }
}

// Функція для зручного виведення тексту на екран
void displayMessage(String line1, String line2) {
 mylcd.clear();
 mylcd.setCursor(0, 0);
 mylcd.print(line1);
 mylcd.setCursor(0, 1);
 mylcd.print(line2);
}