void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:
  //input parameters
double desiredValue = 14.5;  // 100kPa in psi
double tolerance = 0.5;
int pumpPin = 5;
int inletValvePin = 6;
int exhaustValvePin = 7;
int ledPin = 13;
int analogInPin = A0;
int reference_voltage_mv = 9;
int ADCFULLSCALE = 10;
double Pmax = 0.9;
double Pmin = 0.7;



//inflation & deflation 
                    
if ( digitalRead(2) == HIGH) {
digitalWrite(inletValvePin,HIGH); // turn pressure valve HIGH
digitalWrite(pumpPin,HIGH); // make sure pump is on
digitalWrite(exhaustValvePin,LOW); // turn exhaust valve LOW
digitalWrite(ledPin,HIGH); // LED ON
}

if ( digitalRead(2) == LOW) {
digitalWrite(inletValvePin,LOW); // turn pressure valve HIGH
digitalWrite(pumpPin,LOW); // pump is off
digitalWrite(exhaustValvePin,HIGH); // turn exhaust valve HIGH
digitalWrite(ledPin,LOW); // LED off
}

int sensorValue = analogRead(analogInPin);
// digital value of pressure sensor voltage
double voltage_mv =  (sensorValue * reference_voltage_mv) / ADCFULLSCALE;
 
// pressure sensor voltage in mV
double voltage_v = voltage_mv / 1000; 
                                     
double output_pressure = ( ( (voltage_v - (0.10 * (reference_voltage_mv/1000) )) * (Pmax - Pmin) ) / (0.8 * (reference_voltage_mv/1000) ) ) + Pmin;


//FSM Control



if (sensorValue <= desiredValue) {
analogWrite(pumpPin,255); // Pump. (0 is off) and (255 is on)
digitalWrite(inletValvePin,HIGH); // open the air valve
digitalWrite(exhaustValvePin,LOW); // close the exhaust valve
}

if (sensorValue > desiredValue) {
  while (analogRead(A0) > (desiredValue - tolerance) ) {
  analogWrite(pumpPin,190); // reduce speed of pump
  digitalWrite(inletValvePin,HIGH); // open the air valve
  digitalWrite(exhaustValvePin,LOW); // close the exhaust valve
  }
}


}
