import processing.serial.*;
Serial myPort;
float xPos;

void setup(){
  size(800,600);
  
  //println(Serial.list());
  String portName = Serial.list()[5];
  myPort = new Serial (this, portName, 9600);
  // myPort.bufferUntil('\n');
}
// 
void draw(){
  background(0);
  fill(255);
  noStroke();
  ellipse(xPos, height/2, 40, 40);
  ellipse(xPos-10, height/2 - 20, 10, 30); 
  ellipse(xPos+10, height/2 - 20, 10, 30); 
}

void serialEvent (Serial myPort) {
  float inByte = myPort.read();
  println(inByte);
  xPos = map(inByte, 160, 190, 0, width);
  myPort.write('x');
}
