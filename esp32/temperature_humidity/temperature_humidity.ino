#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C mylcd(0x27, 16, 2);
const int STEAM_PIN = 34;
void setup() {
  Serial.begin(9600);
  pinMode(STEAM_PIN, INPUT);
  Wire.begin(21, 22);
  mylcd.init();
  mylcd.backlight();
  mylcd.clear();
  mylcd.setCursor(0, 0);
  mylcd.print("Steam Sensor");
  mylcd.setCursor(0, 1);
  mylcd.print("Initializing...");
  delay(2000);
  mylcd.clear();
}

void loop() {
  int rawValue = analogRead(STEAM_PIN);
  int steamPercent = map(rawValue, 0, 4095, 0, 100);
  Serial.print("Raw ADC: ");
  Serial.print(rawValue);
  Serial.print(" | Percent: ");
  Serial.println(steamPercent);
  mylcd.setCursor(0, 0);
  mylcd.print("Raw Val: ");
  mylcd.print(rawValue);
  mylcd.print("     "); // Очищення залишків старих цифр
  mylcd.setCursor(0, 1);
  mylcd.print("Steam: ");
  mylcd.print(steamPercent);
  mylcd.print("% ");
  if (steamPercent < 15) {
    mylcd.print("[Dry] ");
  } else if (steamPercent >= 15 && steamPercent < 60) {
    mylcd.print("[Wet] ");
  } else { 
    mylcd.print("[STEAM]"); 
  }
  delay(500);
}