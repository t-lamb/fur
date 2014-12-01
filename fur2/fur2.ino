void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
}

void loop() {
  int analogValue0 = analogRead(A0);
  //Serial.print(analogValue0/4);
  //Serial.print(",");
  int analogValue1 = analogRead(A1);
  //Serial.print(analogValue1/4);
  //Serial.print(",");
  int analogValue2 = analogRead(A2);
  //Serial.print(analogValue2/4);
  //Serial.print(",");
  int analogValue3 = analogRead(A3);
  //Serial.print(analogValue3/4);
  //Serial.print("\n");

  //find average of one side
  int ave0 = (analogValue0+analogValue1)/2;
  Serial.print(ave0/4);
  Serial.print(",");
  //find average of other side
  int ave1 = (analogValue2+analogValue3)/2;
  Serial.print(ave1/4);
  Serial.print("\n");
}
