import processing.serial.*;
Serial myPort;

float yPos0 = 0;
float yPos1 = 0;
float yPos2 = 0;
float yPos3 = 0;

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
  fill(204, 255, 153);
  ellipse(100, yPos0, 40, 40);
  ellipse(100-10, yPos0 - 20, 10, 30); 
  ellipse(100+10, yPos0 - 20, 10, 30); 

  //blue
  fill(204, 229, 255);
  ellipse(200, yPos1, 40, 40);
  ellipse(200-10, yPos1 - 20, 10, 30); 
  ellipse(200+10, yPos1 - 20, 10, 30); 

  //white
  fill(255);
  ellipse(300, yPos2, 40, 40);
  ellipse(300-10, yPos2 - 20, 10, 30); 
  ellipse(300+10, yPos2 - 20, 10, 30);

  //yellow
  fill(255,255,153);
  ellipse(400, yPos3, 40, 40);
  ellipse(400-10, yPos3 - 20, 10, 30); 
  ellipse(400+10, yPos3 - 20, 10, 30);
  
}

void serialEvent (Serial myPort) {
  String input = myPort.readStringUntil('\n');
  if (input != null) {
    println(input);
    
    input = trim(input);
    int values[] = int(split(input, ','));
    
    if (values.length == 4){
    yPos0 = map(values[0], 100, 200, 0, height);
    yPos1 = map(values[1], 100, 200, 0, height);
    yPos2 = map(values[2], 100, 200, 0, height);
    yPos3 = map(values[3], 100, 200, 0, height);
    myPort.write('x');
    }
  }
}
