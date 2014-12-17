int base0 = 0;
int base1 = 0;
int base2 = 0;

int base0total; 
int base1total;
int base2total;

int new0 = 0;
int new1 = 0;
int new2 = 0;

int new0total = 0; 
int new1total = 0;
int new2total = 0;

int diff0 = 0;
int diff1 = 0;
int diff2 = 0;

boolean firstRead = true;
boolean pressed0 = false;
boolean pressed1 = false;
boolean pressed2 = false;
int threshold0 = 10;
int threshold1 = 7;
int threshold2 = 7;

int count = 0;
int countMax = 10;

unsigned long start, finished, elapsed;

const int vibPin = 3;
const int ledPinRed = 5;
const int ledPinGreen = 6;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0,0");

  pinMode(vibPin, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
}

void loop() {
  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);
  int analogValue2 = analogRead(A2);

  count++;

  if(firstRead){
    digitalWrite(vibPin, LOW);
    digitalWrite(ledPinRed, LOW);
    analogWrite(ledPinGreen, 0);

    // total first set of readings
    base0total += analogValue0;
    base1total += analogValue1;
    base2total += analogValue2;

    // find base average
    if (count == countMax) {
      base0 = base0total/count;
      base1 = base1total/count;
      base2 = base2total/count;

      firstRead = false;
      count = 0;
    }
  } 
  else { // all readings after first
    // total new set of readings
    new0total += analogValue0;
    new1total += analogValue1;
    new2total += analogValue2;

    //find new average
    if (count == countMax){
      new0 = new0total/count;
      new1 = new1total/count;
      new2 = new2total/count;

      diff0 = new0 - base0;
      diff1 = new1 - base1;
      diff2 = new2 - base2;

      //      Serial.print(diff0);
      //      Serial.print(",");
      //      Serial.print(diff1);
      //      Serial.print(",");
      //      Serial.println(diff2);

      // if left is pressed, check for movement
      digitalWrite(ledPinRed, LOW);

      // if left is pressed, check for movement      
      if (pressed0) {
        // if moves from left to middle
        if (diff0 <= 0 && diff1 > 4) { 
          digitalWrite(vibPin, HIGH);
          digitalWrite(ledPinGreen, HIGH);
          Serial.println("pet>>"); 
        }
      }
      if (pressed1) {
        if (diff0 > threshold0) {
          //digitalWrite(vibPin, HIGH);
          pressed0 = true;
        }
      }
      if (pressed2) {
        if (diff2 < 0 && diff1 > threshold1) {

          pressed2 = false;
        }
      }

      // check all thresholds every round  
      if (diff0 > threshold0){
        pressed0 = true;
        //        start = millis();         
        //        Serial.println("left");
      }
      if (diff1 > threshold1){
        //        Serial.println("middle");
      }
      if (diff2 > threshold2){
        digitalWrite(vibPin, LOW);
        digitalWrite(ledPinGreen, LOW);
        pressed2 = true;
        //        Serial.println("right");
      }

      delay(1);
      base0 = new0;
      base1 = new1;
      base2 = new2;  

      new0total = 0;
      new1total = 0;
      new2total = 0;

      count = 0;  
    }
  }
}
