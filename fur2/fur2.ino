int base0 = 0;
int base1 = 0;
int base2 = 0;
int base3 = 0;

int base0total; 
int base1total;
int base2total;
int base3total;

int new0 = 0;
int new1 = 0;
int new2 = 0;
int new3 = 0;

int new0total =0 ; 
int new1total = 0;
int new2total = 0;
int new3total = 0;

int diff0 = 0;
int diff1 = 0;
int diff2 = 0;
int diff3 = 0;

boolean firstRead = true;
int count = 0;
int numRead = 10;
int threshold = 20;

const int vibPin = 3;
const int ledPin0 = 5;
const int ledPin1 = 6;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0,0,0,0");
  // set vibration motor 
  //pinMode(vibPin, OUTPUT);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);
}

void loop() {
  // vibration is off
  //digitalWrite(vibPin, LOW);
  //delay(2000);
  
  digitalWrite(ledPin0, LOW);
  digitalWrite(ledPin1, LOW);
  
  // read pins
  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);
  int analogValue2 = analogRead(A2);
  int analogValue3 = analogRead(A3);
  
  
//  analogWrite(vibPin, analogValue2/4);
//  analogWrite(ledPin, analogValue3/4);

  //start counter
  count++;
//
//  // if this is the first reading
 if(firstRead) {
   // gather first set of readings
    base0total += analogValue0; 
    base1total += analogValue1;
    base2total += analogValue2;
    base3total += analogValue3; 
//    // find first average
    if (count == numRead){
      count = 0;
      base0 = base0total/count;
      base1 = base1total/count;
      base2 = base2total/count;
      base3 = base3total/count;
      firstRead = false;     
    }
  } 
  else { // if sunbsequent reading
    // gather new set of readings
    new0total += analogValue0; 
    new1total += analogValue1;
    new2total += analogValue2;
    new3total += analogValue3;
    // find new average
//    Serial.println(count);
    if (count == numRead){
      new0 = new0total/count;
      new1 = new1total/count;
      new2 = new2total/count;
      new3 = new3total/count;

      // find and print differences
//      Serial.print(new0);
//      Serial.print(" - ");
//      Serial.print(base0);
//      Serial.print(" = ");
      diff0 = new0 - base0;
//      Serial.print(diff0);
//      Serial.print(",");
      diff1 = new1 - base1;
//      Serial.print(diff1);
//      Serial.print(",");
      diff2 = new2 - base2;
//      Serial.print(diff2);
//      Serial.print(",");
//      Serial.print(new3);
//      Serial.print(" - ");
//      Serial.print(base3);
//      Serial.print(" = ");
//      Serial.print(analogValue3);
      diff3 = new3 - base3;
//      Serial.print(diff3);
//      Serial.print("\n");
      if(diff0 > threshold){
        digitalWrite(ledPin0, HIGH);
      }
      if(diff1 > threshold){
        digitalWrite(ledPin0, HIGH);
      }
      if(diff2 > threshold){
        digitalWrite(ledPin1, HIGH);
      }
      if(diff3 > threshold){
        digitalWrite(ledPin1, HIGH);
      }
      delay(50);

      //
//      digitalWrite(vibPin, HIGH);
//delay(100);

      // set new readings as base
      base0 = new0;
      base1 = new1;
      base2 = new2;
      base3 = new3;
      new0total = 0;
      new1total = 0;
      new2total = 0;
      new3total = 0;

      // reset counter
      count = 0;
    }
  }
}
