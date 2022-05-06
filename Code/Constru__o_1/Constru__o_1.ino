#define Lred 6
#define Lgreen 7
#define Sgas 2
#define Buz 10
#define valv 13
#define sw 3

void setup() {
  pinMode(Lred, OUTPUT);
  pinMode(Lgreen, OUTPUT);
  pinMode(Buz, OUTPUT);
  pinMode(Sgas, INPUT);
  pinMode(valv, OUTPUT);
  pinMode(sw, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sw), valvrest, FALLING);
}

void loop() {
  if(digitalRead(Sgas) == HIGH) {
    digitalWrite(Lred, HIGH);
    digitalWrite(Lgreen, LOW);
    tone(Buz, 500);
    digitalWrite(valv, HIGH);
  }
  else {
    digitalWrite(Lgreen, HIGH);
    digitalWrite(Lred, LOW);
    noTone(Buz);
  }
  delay(500);
}

void valvrest() {
  digitalWrite(valv, LOW);
}
