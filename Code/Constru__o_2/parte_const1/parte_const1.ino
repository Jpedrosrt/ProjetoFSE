#include <LiquidCrystal.h>
#include <HX711.h>

LiquidCrystal lcd(12, 11, 6, 5, 4, 9);

#define Lred 7
#define Lgreen 8
#define Sgas 2
#define Buz 10
#define valv 13
#define sw 3
#define DT A1
#define SCK A2

long DIF = 14680;

HX711 loadcell;

unsigned long a;
int typb = 13;
int bvz;
int b;
int c;
int d = 100;
long timer;

long timer2 = 0;
bool gaswasdetc = false;
bool aux = false;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("Detector de");
  lcd.setCursor(12,1);
  lcd.print("Gas");
  delay(1000);
  loadcell.begin(DT, SCK);
  calibrate();
  pinMode(Lred, OUTPUT);
  pinMode(Lgreen, OUTPUT);
  pinMode(Buz, OUTPUT);
  pinMode(Sgas, INPUT);
  pinMode(valv, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw), valvrest, FALLING);
}

void loop() {
  a = loadcell.read_average();
  b = a/DIF;
  //Serial.println(bvz);
  c = ((b - bvz) * 100) / typb;
  
  timer = millis();

  if (timer == 80) {
    timer2 = 0;
  }
  
  if(c != d) {
    d = c;
    if((timer - timer2) < 6000) { //61200000
      aux = true;
    }
    timer2 = timer;
  }
  
  if(digitalRead(Sgas) == HIGH || aux) {
    digitalWrite(Lred, HIGH);
    digitalWrite(Lgreen, LOW);
    tone(Buz, 500);
    digitalWrite(valv, HIGH);
    lcd.setCursor(0,0);
    if(aux) { 
      lcd.print("    GAS LEAK    ");
    } else {
      lcd.print("  GAS DETECTED  ");
    }
    lcd.setCursor(0,1);
    gaswasdetc = true;
    lcd.print("LEVEL: ");
    lcd.setCursor(7,1);
    lcd.print(c);
    if(c < 100) {
      lcd.setCursor(9,1);
    }
    else {
      lcd.setCursor(10,1);
    }
    lcd.print("% ");
  }
  else {
    digitalWrite(Lgreen, HIGH);
    digitalWrite(Lred, LOW);
    noTone(Buz);
    lcd.setCursor(0,0);
     if (!gaswasdetc){
      lcd.print("GAS NOT DETECTED");
    } else {
      lcd.print("GAS WAS DETECTED");
    }
    lcd.setCursor(0,1);
    lcd.print("LEVEL: ");
    lcd.setCursor(7,1);
    lcd.print(c);
    if(c < 100 && c > 9) {
      lcd.setCursor(9,1);
    }
    else if(c < 10){
      lcd.setCursor(8,1);
    }
    else {
      lcd.setCursor(10,1);
    }
    lcd.print("% ");
  }
  
  delay(500);
}

void calibrate() {
  lcd.clear();
  lcd.print("Calibrating...");
  delay(2000);
  a = loadcell.read_average();
  b = a/DIF;
  bvz = b - typb;
  lcd.clear();
}

void valvrest() {
  gaswasdetc = false;
  aux = false;
  digitalWrite(valv, LOW);
}
