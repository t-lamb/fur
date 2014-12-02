import processing.serial.*;
Serial myPort;

float s0 = 0;
float s1 = 0;
float s2 = 0;
float s3 = 0;

void setup() {
  size(800, 600);

  //println(Serial.list());
  String portName = Serial.list()[5];
  myPort = new Serial (this, portName, 9600);
  myPort.bufferUntil('\n');
}

void draw() {
  background(0);
  
  noStroke();
  //green
  fill(204, 255,153);
  ellipse(s0, 2*(height/3), 40, 40);
  
  //blue
  fill(204, 229, 255);
  ellipse(s1, height/3, 40, 40);
  
  //white
  fill(255);
  ellipse(s2, height/3, 40, 40);
  
  //yellow
  fill(255, 255, 153);
  ellipse(s3, 2*(height/3), 40, 40);
}

void serialEvent (Serial myPort) {
  //read serial buffer:
  String inputString = myPort.readStringUntil('\n');
  if (inputString != null) {
    println(inputString);
    
    inputString = trim(inputString);
    int values[] = int(split(inputString, ','));
    
    if(values.length == 4) {
      s0 = map(values[0], 100, 255, 0, width/2);
      s1 = map(values[1], 100, 255, 0, width/2);
      s2 = map(values[2], 100, 255, width/2, width);
      s3 = map(values[3], 100, 255, width/2, width);
    }
  }
}
