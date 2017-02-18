
#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10);
const uint64_t pipe1 = 0xE8E8F0F0E1LL;
char cmd[8] = {0xAA};

void setup() {
  Serial.begin(9600);
  //
  // Setup radio pipe
  //
  radio.begin();

  radio.setPALevel(RF24_PA_LOW); // one of RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH and RF24_PA_MAX
  radio.setDataRate(RF24_250KBPS); // RF24_250KBPS for 250kbs, RF24_1MBPS for 1Mbps, or RF24_2MBPS for 2Mbps
  radio.setChannel(42); // Which RF channel to communicate on, 0-125
  radio.setAutoAck(1);                     // Ensure autoACK is enabled
  radio.setRetries(3, 30);                 // Optionally, increase the delay between retries & # of retries
  radio.powerUp();

  radio.openWritingPipe(pipe1);

  radio.printDetails();
}

void loop() {
  
  if ( Serial.available() > 0 ) {
    cmd[0] = Serial.read();
//    if ( cmd[0] == 'o' ) {
      //while  ( !radio.write( &cmd, 8 ) );
    radio.write( cmd, 8 );
    delay(100);
    Serial.write( "Sent opening command...\r\n" );
    Serial.println( cmd[0] );
    Serial.flush();
      //   pinMode(lock_pin, OUTPUT);
      //   digitalWrite(lock_pin, LOW);
      //   delay(1000);
      //   pinMode(lock_pin, INPUT);
//    }
  }
}
