int base0 = 0;
int base1 = 0;
int base2 = 0;
int base3 = 0;

int diff0 = 0;
int diff1 = 0;
int diff2 = 0;
int diff3 = 0;

boolean firstRead = true;
int count = 0;

const int vibPin = 3;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0,0,0,0");

  pinMode(vibPin, OUTPUT);
}

void loop() {
  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);
  int analogValue2 = analogRead(A2);
  int analogValue3 = analogRead(A3);

  digitalWrite(vibPin, LOW);

  //if this is the first reading
  if(firstRead) {
    count++;
    base0total += analogValue0; 
    base1total += analogValue1;
    base2total += analogValue2;
    base3total += analogValue3;
    //subsequent readings will be false 

    if (count == 40){
      base0 = base0total/count;
      base1 = base1total/count;
      base2 = base2total/count;
      base3 = base3total/count;
      firstRead = false;
    }
  }

  diff0 = analogValue0 - base0;
  delay(1);

  diff1 = analogValue1 - base1;
  delay(1);

  diff2 = analogValue2 - base2;
  delay(1);

  diff3 = analogValue3 - base3;
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




