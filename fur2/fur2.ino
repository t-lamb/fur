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
    analogWrite(vibPin, 0);
    analogWrite(ledPin0, 0);
    digitalWrite(ledPin1, LOW);

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


      //      if (diff0 > 12){
      //        int vibVal = map(new0, 0, 1023, 0, 255);
      //        constrain(vibVal, 0, 50);
      //        analogWrite(ledPin0, vibVal);
      //        Serial.println(vibVal);
      //      } else {
      //        analogWrite(ledPin0, 0);
      //      }
      //Serial.println(diff0);
      
      if (leftPressed){
        int vibVal = map(new0, 0, 1023, 0, 255);
        constrain(vibVal, 0, 50);
        analogWrite(ledPin0, vibVal);
        Serial.println(vibVal);
        // check left pin        
        if (diff0 > 12){
          //left is still pressed
          analogWrite(ledPin0, vibVal);
        } 
        else if (diff1 > 7){
          //direction is correct
          Serial.println("moving right");
          analogWrite(ledPin0, vibVal);
          leftPressed = false;
          rightPressed = true;
        } 
        else {
          //neither is pressed
          leftPressed = false;
          rightPressed = false;
          analogWrite(ledPin0, 0);       
        } 
      }
      
      if (diff0 > 12){
        leftPressed = true;
      } else { 
        leftPressed = false;
      }
      
      if (diff1 > 7){
        rightPressed = true;
      } else {
        rightPressed = false;
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












