#include <VirtualWire.h>
#include <HX711.h>

#define DT A1
#define SCK A2
#define tx 12

long DIF = 14680;

HX711 loadcell;

unsigned long a;
int typb = 13;
int bvz;
int b;
int c;

void setup() {
  vw_set_ptt_inverted(true);
  vw_set_tx_pin(tx);
  vw_setup(4000);
  loadcell.begin(DT, SCK);
  calibrate();
}
 
void loop(){ 
  a = loadcell.read_average();
  b = a/DIF;
  //Serial.println(bvz);
  c = ((b - bvz) * 100) / typb;
  vw_send((uint8_t *)c, strlen(c));
  vw_wait_tx();
  //lcd.setCursor(0,0);
  //lcd.print("  NIVEL:    ");
  //lcd.print(c);
  //lcd.print("%  ");
}

void calibrate() {
  //lcd.clear();
  //lcd.print("Calibrating...");
  //delay(2000);
  a = loadcell.read_average();
  b = a/DIF;
  bvz = b - typb;
  //lcd.clear();
}
