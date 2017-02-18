#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

int lock_pin = 2;

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  radio.begin();
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
  Serial.begin(9600);
  pinMode(lock_pin, INPUT);
}

void loop() {
// if there is data ready
  uint8_t cmd;
  if ( radio.available() )
  {
    // Dump the payloads until we've gotten everything
    while (radio.available())
    {
      // Fetch the payload, and see if this was the last one.
      radio.read( cmd, 1 );
      if( cmd == 'o' ) {
        Serial.write( "Opening...\r\n" );
        pinMode(lock_pin, OUTPUT);
        digitalWrite(lock_pin, LOW);
        delay(1000);
        pinMode(lock_pin, INPUT);
      }
    }
  }
}
