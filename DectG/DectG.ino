#include <LiquidCrystal.h>


LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Buz = 10; 
int Sgas = 9;
int Lgreen = 7;
int Lred = 6;


void setup() {
  pinMode(Sgas, INPUT);
  pinMode(Buz, OUTPUT);
}

void loop() {
  if(digitalRead(Sgas) == HIGH) {
    lcd.setCursor(0,0);
    lcd.print("  Gas Detected  ");
    digitalWrite(Lred, HIGH);
    digitalWrite(Buz, HIGH);
    digitalWrite(Lgreen, LOW);
  }
  else {
    lcd.setCursor(0,0);
    lcd.print("Gas not Detected");
    digitalWrite(Lred, LOW);
    digitalWrite(Buz, LOW);
    digitalWrite(Lgreen, HIGH);
  }
  delay(500);
  lcd.clear();
}