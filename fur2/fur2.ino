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
int threshold0 = 20;
int threshold1 = 20;
int threshold2 = 15;

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
    analogWrite(ledPinRed, 0);
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

//      Serial.println(diff0);
//      Serial.print(",");
//      Serial.print(diff1);
//      Serial.print(",");
//      Serial.println(diff2);

      // if left is pressed, check for movement
      if (pressed0) {
        // if left still pressed
        if (diff0 > threshold0) {
          Serial.println("left");
          pressed0 = true;
        }
        // if moving right
        else if (diff1 > threshold1) { 
         // timer end
         finished = millis();
         elapsed = finished - start;
         pressed0 = false;
         pressed1 = true;  
         Serial.println("left middle");     
        }
      }
      if (pressed1) {
        if (diff0 > threshold0) {
         digitalWrite(vibPin, HIGH);
         delay(elapsed);
         digitalWrite(vibPin, LOW);
         Serial.println("middle");
         pressed0 = true;
        }
      }
      if (pressed2) {
        digitalWrite(vibPin, LOW);
        int brightnessRed = analogValue2/4;
        analogWrite(ledPinRed, brightnessRed);
        Serial.println("right");
      }
      
      // check all thresholds every round  
      if (diff0 > threshold0){
          pressed0 = true;
          // light turns on when first pressed
          int brightnessGreen = analogValue0/4;
          analogWrite(ledPinGreen, brightnessGreen);
          start = millis();         
//        Serial.println("left");
      }
      if (diff1 > threshold1){
          pressed1 = true;
//        Serial.println("middle");
      }
      if (diff2 > threshold2){
          pressed2 = true;
//        Serial.println("right");
      }

      delay(50);
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



