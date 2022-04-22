#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 9);
int Buz = 10; 
int Sgas = 2;
int Lgreen = 7;
int Lred = 6;


void setup() {
  attachInterrupt(0, gasdetec, RISING);
  attachInterrupt(0, gasndetec, FALLING);
}

void gasdetec() {
  lcd.setCursor(0,0);
  lcd.print("Gas Detected: Yes");
  digitalWrite(Lred, HIGH);
  digitalWrite(Lgreen, LOW);    
}

void gasndetec() {
  pinMode(Sgas, INPUT);
  lcd.setCursor(0,0);
  lcd.print("Gas Detected: No");
  digitalWrite(Lgreen, HIGH);
  digitalWrite(Lred, LOW);
}

void loop() {

}
