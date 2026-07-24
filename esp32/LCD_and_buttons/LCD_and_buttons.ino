#define btn1 16
#define btn2 27
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd (0x27,16,2);

void setup() {
  Serial.begin(9600);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Press any button");
  delay(500);
}

void loop() {
  while(digitalRead(btn1) == 0){
    lcd.setCursor(0, 0);
    lcd.print("First Button 16 ");
    lcd.setCursor(0, 1);
    lcd.print("is pressed");
  }
  while (digitalRead(btn2) == 0) {
    lcd.setCursor(0, 0);
    lcd.print("Second Button 27 ");
    lcd.setCursor(0, 1);
    lcd.print("is pressed");
  }
  boolean btn1_val = digitalRead(btn1);
  boolean btn2_val = digitalRead(btn2);
  if (btn2_val && btn1_val) {
    lcd.setCursor(0, 0);
    lcd.print("Press any button");
    lcd.setCursor(0, 1);
    lcd.print("                ");
  }
  delay(100);
}