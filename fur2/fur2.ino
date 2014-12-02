int base0 = 0;
int base1 = 0;
int base2 = 0;
int base3 = 0;

int diff0 = 0;
int diff1 = 0;
int diff2 = 0;
int diff3 = 0;

boolean firstRead = true;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0,0,0,0");
}

void loop() {
  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);
  int analogValue2 = analogRead(A2);
  int analogValue3 = analogRead(A3);

  //if this is the first reading
  if(firstRead) {
    base0 = analogValue0; 
    base1 = analogValue1;
    base2 = analogValue2;
    base3 = analogValue3;
    //subsequent readings will be false 
    firstRead = false;
  }

  diff0 = base0 - analogValue0;
  delay(1);

  diff1 = base1 - analogValue1;
  delay(1);

  diff2 = base2 - analogValue2;
  delay(1);

  diff3 = base3 - analogValue3;
  delay(1);

  Serial.print(diff0);
  Serial.print(",");
  Serial.print(diff1);
  Serial.print(",");
  Serial.print(diff2);
  Serial.print(",");
  Serial.print(diff3);
  Serial.print("\n");

}



