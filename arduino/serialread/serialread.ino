
#define TEST_PORT (4)

void setup() {
  // Initialize digital pins 2 to 9 as outputs
  for (int pin = 2; pin <= 9; pin++) {
    pinMode(pin, OUTPUT);
  }
  pinMode(TEST_PORT, OUTPUT);

  // Start serial communication at 9600 baud
  Serial.begin(9600);
  digitalWrite(TEST_PORT, 0x01);
}

void loop1() {
  /*
  delay(500);
  digitalWrite(10, 1);
  delay(500);
  digitalWrite(10, 0);
  */
  if (Serial.available() > 0) {
    // Read one byte from serial
    byte inputByte = Serial.read();

    digitalWrite(TEST_PORT, 0x01 & inputByte);
    /*
    // Output each bit to corresponding digital pin (LSB on pin 2)
    for (int i = 0; i < 8; i++) {
      digitalWrite(2 + i, (inputByte >> i) & 0x01);
    }
    */
  }
}

bool forward = true;
int onbit = 0;

void loop2() {
  int laston = onbit;

  if (Serial.available() > 0) {
    // Read one byte from serial
    byte inputByte = Serial.read();
    if ((inputByte & 0x01) == 0) {
      forward = true;
    } else {
      forward = false;
    }
  }
  
  if (forward) {
    onbit = (onbit + 1) % 8;
  } else {
    onbit = (onbit + 7) % 8;
  }

  digitalWrite(2 + onbit, 1);
  
  digitalWrite(2 + laston, 0);

  delay(100);
}

void loop() {
  loop2();
}
