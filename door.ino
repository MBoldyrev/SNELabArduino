int lock_pin = 2;    

void setup() {
  Serial.begin(9600);
  pinMode(lock_pin, INPUT);
}

void loop() {
  if (Serial.available() > 0) {
    int cmd = Serial.read();
    if( cmd == 'o' ) {
      Serial.write( "Opening...\r\n" );
      pinMode(lock_pin, OUTPUT);
      digitalWrite(lock_pin, LOW);
      delay(1000);
      pinMode(lock_pin, INPUT);
    }
  }
}
