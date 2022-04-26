
#define Lred 6
#define Lgreen 7
#define Sgas 2
#define Buz 10

void setup() {
  pinMode(Lred, OUTPUT);
  pinMode(Lgreen, OUTPUT);
  pinMode(Buz, OUTPUT);
  pinMode(Sgas, INPUT);
}

void loop() {
  if(digitalRead(Sgas) == HIGH) {
    digitalWrite(Lred, HIGH);
    digitalWrite(Lgreen, LOW);
    tone(Buz, 500);
  }
  else {
    digitalWrite(Lgreen, HIGH);
    digitalWrite(Lred, LOW);
    noTone(Buz);
  }
  delay(500);
}
