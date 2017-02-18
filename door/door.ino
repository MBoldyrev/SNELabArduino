#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "stdio.h"

int lock_pin = 2;

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;
char cmd[8] = {0};

void setup() {
  radio.begin();

  radio.setPALevel(RF24_PA_LOW); // one of RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS); // RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setChannel(42); // Which RF channel to communicate on, 0-125
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(3, 30);                 // Optionally, increase the delay between retries & # of retries
  radio.powerUp();
  
  radio.openReadingPipe(1,pipe);
  radio.startListening();
  
  Serial.begin(9600);
  pinMode(lock_pin, INPUT);
}

void loop() {
// if there is data ready
  if ( radio.available() )
  {
    // Dump the payloads until we've gotten everything
    while (radio.available())
    {
      // Fetch the payload, and see if this was the last one.
      radio.read( cmd, 8 );
      Serial.write( "Got command...\r\n" );
      Serial.println( cmd[0] );
      delay(100);
      Serial.flush();
      if( cmd[0] == 'o' ) {
        Serial.write( "Opening...\r\n" );
        pinMode(lock_pin, OUTPUT);
        digitalWrite(lock_pin, LOW);
        delay(1000);
        pinMode(lock_pin, INPUT);
      }
    }
  }
}
