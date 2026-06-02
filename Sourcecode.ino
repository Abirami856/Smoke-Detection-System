#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo myServo;

int gasPin = A0;
int buzzerPin = 8;
int servoPin = 9;

int gasValue = 0;
int threshold = 400;   // Adjust this value

void setup() {
  pinMode(buzzerPin, OUTPUT);
  myServo.attach(servoPin);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("Gas Monitor");
  lcd.setCursor(0, 1);
  lcd.print("System Ready");
  delay(2000);
  lcd.clear();

  myServo.write(0);   // Servo initial position
}

void loop() {
  gasValue = analogRead(gasPin);

  lcd.setCursor(0, 0);
  lcd.print("Gas Value: ");
  lcd.print(gasValue);
  lcd.print("   ");

  if (gasValue > threshold) {
    digitalWrite(buzzerPin, HIGH);
    myServo.write(90);   // Open window / valve

    lcd.setCursor(0, 1);
    lcd.print("GAS ALERT!   ");
  } else {
    digitalWrite(buzzerPin, LOW);
    myServo.write(0);

    lcd.setCursor(0, 1);
    lcd.print("Safe Level   ");
  }

  delay(500);
}
