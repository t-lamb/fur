void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  int analogValue0 = analogRead(A0)/4;
  Serial.print(analogValue0);
  Serial.print(",");
  int analogValue1 = analogRead(A1)/4;
  Serial.print(analogValue1);
  Serial.print(",");
  int analogValue2 = analogRead(A2)/4;
  Serial.print(analogValue2);
  Serial.print(",");
  int analogValue3 = analogRead(A3)/4;
  Serial.print(analogValue3);
  Serial.print("\n");
}
