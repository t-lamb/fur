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
boolean leftPressed = false;
boolean rightPressed = false;
count++;
countMax = 10;
threshold = 20;

//const int vibPin = 3;
//const int ledPin0 = 5;
//const int ledPin1 = 6;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  Serial.println("0,0,0,0");

  //pinMode(vibPin, OUTPUT);
  //pinMode(ledPin0, OUTPUT);
  //pinMode(ledPin1, OUTPUT);

}

void loop() {
  readValues();
  checkValues();
  reset();

  //  digitalWrite(ledPin0, LOW);
  //  digitalWrite(ledPin1, LOW);
}

readValues() {
  int analogValue0 = analogRead(A0);
  int analogValue1 = analogRead(A1);
  int analogValue2 = analogRead(A2);
  int analogValue3 = analogRead(A3);

  count++;

  if(firstRead) { // first run
    base0total += analogValue0;
    base1total += analogValue1;
    base2total += analogValue2;
    base3total += analogValue3;

    if(count == countMax){
      base0 = base0total/count;
      base1 = base1total/count;
      base2 = base2total/count;
      base3 = base3total/count;

      count = 0;
      firstRead = false;
    } 
  } 
  else { // all subsequent runs
    new0total += analogValue0;
    new1total += analogValue1;
    new2total += analogValue2;
    new3total += analogValue3;

    if(count == countMax){
      new0 = new0total/count;
      new1 = new1total/count;
      new2 = new2total/count;
      new3 = new3total/count;
    }
  }
}

checkValues() {
  diff0 = new0 - base0;
  diff1 = new1 - base1;
  diff2 = new2 - base2;
  diff3 = new3 - base3;

  if (leftPressed) {
    if (rightPressed){
      // both are pressed
    } 
    else { // if only left is pressed, check for movement  
      if (diff0 > threshold || diff1 > threshold){
        // left is still pressed
      } 
      else if (diff2 > threshold || diff3 > threshold) {
        //direction is correct
        leftPressed = false;
        rightPressed = true;
      }
      else {
        // neither is pressed
        leftPressed = false;
        rightPressed = false; 
      }
    } 
  } 
  else if (rightPressed){
    if (diff2 > threshold || diff3 > threshold){
      // right is still pressed 
    } 
    else if (diff0 > threshold || diff1 > threshold) {
      //direction is wrong
      leftPressed = true;
      rightPressed = false;
    } 
    else {
      // neither is pressed
      leftPressed = false;
      rightPressed = false;
    }
  }
  else { 
    if (diff0 > threshold || diff1 > threshold){
      leftPressed = true;
    }

    if (diff2 > threshold || diff3 > threshold){
      rightPressed = true;
    }
  }
}


reset() {
  base0 = new0;
  base1 = new1;
  base2 = new2;
  base3 = new3;
  new0total = 0;
  new1total = 1;
  new2total = 2;
  new3total = 3;

  count = 0;
}









