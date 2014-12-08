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
const int ledPinRed = 5;
const int ledPinGreen = 6;

void setup(){
  Serial.begin(9600);
  Serial.println("0,0");

  pinMode(vibPin, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);

}

void loop() {

  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);

  count++;

  if(firstRead) {
    digitalWrite(vibPin, LOW);
    analogWrite(ledPinRed, 0);
    analogWrite(ledPinGreen, 0);

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
      
      // if left was prev pressed, check if still pressed
      if (leftPressed){
        if(diff0 < 12){
          leftPressed = true;
        }
        else if(diff1 > 12){
          //timer end
          finished = millis();
          elapsed = finished - start;
          digitalWrite(vibPin,LOW);
          leftPressed = false;    
        }
      }   
      
      // if left is pressed this time
      if (diff0 > 12){
        leftPressed = true;
        // light turns on when first pressed
        int brightnessGreen = analogValue0/4;
        analogWrite(ledPinGreen, brightnessGreen);
        // start vib
        digitalWrite(vibPin, HIGH);
        start = millis();
        delay(elapsed*2);
      } 
      else { 
        // left is unpressed, turn off light, turn off vib
        leftPressed = false;
        analogWrite(ledPinGreen, 0);
        digitalWrite(vibPin, LOW);
      }
      
      // if pressed hard turb on light
      if (diff1 > 40){
         Serial.println(diff1);
        int brightnessRed = analogValue1/4;
        analogWrite(ledPinRed, brightnessRed);
        delay(1);
      }
      else {
        //otherwise turn it off
        analogWrite(ledPinRed, 0);
        delay(1);
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














