// Communicates with 8-channel switch to drive 8 laser diodes
// to create different visual patterns
// 22/04/2023

#include <SPI.h>

unsigned int time_diff = 0;
unsigned int time_curr = 0;

unsigned int period = 1000;

char channels = 0b00000001;

void setup() {
  Serial.begin(115200);
  SPI.beginTransaction(SPISettings(5000000, MSBFIRST, SPI_MODE0));
  SPI.begin();

  delay(500);

  time_curr = millis();
}

void loop() {
time_diff = millis() - time_curr;
if (time_diff > period) {
  time_curr = millis();
  SPI.transfer(channels);
  if(channels == 1){
    channels = 0b00000010;
  }
  else{
    channels = 0b00000001;
  }
}
  

}
