byte desiredValue = 140;  
byte tolerance = 10;
const byte pumpPin = 5; //set
const byte inletValvePin = 6; //set
const byte exhaustValvePin = 7; //set
const byte ledPin = 13; //set
const byte digitalInPin = 9; //set
float reference_voltage_mv = 6000; 
float ADCFULLSCALE = 1023;
float Pmax = 1;
float Pmin = 0;

#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
byte val1 = 0;
byte val2 = 0;

//inflation & deflation 

if ( digitalRead(2) == HIGH) {
digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
analogWrite(pumpPin,255); // make sure pump is on
digitalWrite(exhaustValvePin,LOW); // turn exhaust valve LOW
digitalWrite(ledPin,HIGH); // LED ON
}

if ( digitalRead(2) == LOW) {
digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
analogWrite(pumpPin,0); // pump is off
digitalWrite(exhaustValvePin,HIGH); // turn exhaust valve HIGH
digitalWrite(ledPin,LOW); // LED off
}


//Wire.beginTransmission(byte(0x28)); // transmit to device #44 (0x2c)
                              // device address is specified in datasheet
Wire.requestFrom(byte(0x28), 2);            // sends instruction byte  
val1 = Wire.read();             // sends potentiometer value byte  
     // stop transmitting
val2 = Wire.read();        // increment value

Serial.print(val1, DEC);
Serial.print('\t');
Serial.println(val2, DEC);

delay(500);
  


//FSM Control



if (val2 <= desiredValue) {
analogWrite(pumpPin,255); // Pump. (0 is off) and (255 is on)
digitalWrite(inletValvePin,HIGH); // open the air valve
digitalWrite(exhaustValvePin,LOW); // close the exhaust valve
}

if (val2 > desiredValue) {
  while (val2 > (desiredValue - tolerance) ) {
  analogWrite(pumpPin,0); // reduce speed of pump
  digitalWrite(inletValvePin,HIGH); // open the air valve
  digitalWrite(exhaustValvePin,HIGH); // close the exhaust valve
  Wire.requestFrom(byte(0x28), 2);            // sends instruction byte  
  val1 = Wire.read();             // sends potentiometer value byte  
     // stop transmitting
  val2 = Wire.read();  
  delay(500);
  }

}


}
