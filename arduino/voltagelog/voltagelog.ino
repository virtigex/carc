const int voltagePin = A0;  // Analog pin to read voltage
const float referenceVoltage = 5.0;  // Change if using 3.3V or external reference
const int resolution = 1023;         // 10-bit ADC (0–1023)

// A voltage of 10V to 15V is applied to the top of a resistor
// voltage divider with 2*33kOhm at the top and 33kOhm at the bottom.
//
// Voltage at middle tap is ~ 1/3 of input voltage.

const float scale = 3.1;  // by experiment - theortically 3

void setup() {
  Serial.begin(9600);
  //Serial.println("Time(ms),Voltage(V)");
}

void loop() {
  bool doreading = false;
  
  while (Serial.available()) {
    int inbyte = Serial.read();
    if (inbyte == '\n') {
      doreading = true;
    }
  }

  if (doreading) {
    int sensorValue = analogRead(voltagePin);
    float voltage = scale * (sensorValue * referenceVoltage) / resolution;
    
    Serial.print("{ \"telemetry\" : { \"voltage\": ");
    Serial.print(voltage, 3);
    Serial.println(" } }");
  }
}
