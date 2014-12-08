int base0 = 0;
int base1 = 0;

int base0total; 
int base1total;

int new0 = 0;
int new1 = 0;

int new0total = 0; 
int new1total = 0;

int diff0 = 0;
int diff1 = 0;

boolean firstRead = true;
boolean leftPressed = false;
boolean rightPressed = false;
int count = 0;
int countMax = 10;

unsigned long start, finished, elapsed; 

const int vibPin = 3;
const int ledPin0 = 5;
const int ledPin1 = 6;

void setup(){
  Serial.begin(9600);
  Serial.println("0,0");

  pinMode(vibPin, OUTPUT);
  pinMode(ledPin0, OUTPUT);
  pinMode(ledPin1, OUTPUT);

}

void loop() {

  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);

  count++;

  if(firstRead) {
    digitalWrite(vibPin, LOW);
    analogWrite(ledPin0, 0);
    analogWrite(ledPin1, 0);

    //total first set of readings
    base0total += analogValue0;
    base1total += analogValue1;

    //find base average
    if(count == countMax){
      base0 = base0total/count;
      base1 = base1total/count;

      firstRead = false;
      count = 0;
    } 
  } 
  else { // all subsequent runs
    //total new set of readings
    new0total += analogValue0;
    new1total += analogValue1;

    //find new average
    if(count == countMax){
      new0 = new0total/count;
      new1 = new1total/count;

      diff0 = new0 - base0;
      diff1 = new1 - base1;

      if (leftPressed){
        if(diff0 < 0){
          //start timer end
          finished = millis();
          elapsed = finished - start;
          Serial.println(elapsed);
        }
      }

      if (rightPressed){
        int brightness1 = new1/4;
        if (diff1 > 18) {
          analogWrite(ledPin0, brightness1);
          delay(50);
        }
      }

      if (diff0 > 12){
        leftPressed = true;
        // light turns on when first pressed
        int brightness1 = new0/4;
        analogWrite(ledPin1, brightness1);
        
        digitalWrite(vibPin, HIGH);
        //set timer start
        start = millis();
        delay(50);
        Serial.print("start:");
        Serial.println(diff1);
        delay(elapsed*1.5);
      } 
      else { 
        leftPressed = false;
        analogWrite(ledPin1, 0);
        digitalWrite(vibPin, LOW);
      }

      if (diff1 > 18){
        int brightness0 = new1/4;
        analogWrite(ledPin0, brightness0);
        rightPressed = true;
      }
      else if (diff1 > 7){
        rightPressed = true;
        
      } 
      else {
        rightPressed = false;
        analogWrite(ledPin0, 0);
      }

      delay(50);

      base0 = new0;
      base1 = new1;

      new0total = 0;
      new1total = 0;

      count = 0;
    }
  }
}













