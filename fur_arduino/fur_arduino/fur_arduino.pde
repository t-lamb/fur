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
  fill(204, 255, 153, 100);
  ellipse(width/3, 2*(height/3), s0, s0);

  //blue
  fill(204, 229, 255, 100);
  ellipse(width/3, height/3, s1, s1);

  //white
  fill(255, 100);
  ellipse(2*(width/3), height/3, s2, s2);

  //yellow
  fill(255, 255, 153, 100);
  ellipse(2*(width/3), 2*(height/3), s3, s3);
}
//int renameMe = 0;
void serialEvent (Serial myPort) {
  //renameMe++;

  //if(renameMe % 60 == 0){
  //read serial buffer:
  String inputString = myPort.readStringUntil('\n');
  if (inputString != null) {
    //println(inputString);

    inputString = trim(inputString);
    int values[] = int(split(inputString, ','));

    if (values.length == 4) {
      // s0 = values[0];
      // s1 = values[1];
      // s2 = values[2];
      // s3 = values[3];
      println(values[0]);
      
      s0 = map(values[0], 0, 200, 0, width);
      s1 = map(values[1], 0, 200, 0, width);
      s2 = map(values[2], 0, 200, 0, width);
      s3 = map(values[3], 0, 200, 0, width);
    }
  }
  //}
}

// for(int x = 0; x < 10; x=x+2){
//   //do thing
// }

// int x = 0;
// while(x != -1) {
//   if(x % 2 == 0) {
//   //do thing
//   }
//   x++; 
// }
