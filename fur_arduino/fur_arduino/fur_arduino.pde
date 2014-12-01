import processing.serial.*;
Serial myPort;

float c = 0;

void setup(){
  size(800,600);
  
  //println(Serial.list());
  String portName = Serial.list()[5];
  myPort = new Serial (this, portName, 9600);
  // myPort.bufferUntil('\n');
}
// 
void draw(){
  background(30, 40, c);
}

void serialEvent (Serial myPort) {
  // get the byte:
  int inByte = myPort.read();
  // print it:
  println(inByte);
  c = map(inByte, 0, 40, 0, 255);
}
