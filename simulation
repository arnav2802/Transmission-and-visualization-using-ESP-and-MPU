import controlP5.*;
import processing.opengl.*;
import hypermedia.net.UDP;
import hypermedia.net.*;

ControlP5 cp5; 
PShape rocket;
Chart roll;
Chart pitch;
Chart AccY;
Chart AccZ;
Chart AccX;

UDP udp; 
int port = 6000; 
String ipAddress = "192.168.133.48";
float[] Euler = new float[3];
float[] Acc = new float[3];
float lightValue = 0;
float[] smoothedEuler = new float[3];
float smoothingFactor = 0.1;

float ILSAsenstivity = 11;

PrintWriter dataWriter; 

void setup() {
  // Initialize ControlP5 and UDP
  cp5 = new ControlP5(this);
  udp = new UDP(this, 6000, ipAddress);
  udp.listen(true);
  size(1024, 720, P3D);
  smooth();
  rocket = loadShape("gslv.obj"); 
  roll = cp5.addChart("ROLL")
    .setPosition(1500, 30)
    .setSize(400, 200)
    .setRange(-15, 15)
    .setView(Chart.LINE)
    .setStrokeWeight(2)
    .setColorCaptionLabel(color(40));
  roll.addDataSet("ROLL");
  roll.setData("ROLL", new float[100]);

  pitch = cp5.addChart("PITCH")
    .setPosition(1500, 360)
    .setSize(400, 200)
    .setRange(-15, 15)
    .setView(Chart.LINE)
    .setStrokeWeight(4)
    .setColorCaptionLabel(color(40));
  pitch.addDataSet("PITCH");
  pitch.setData("PITCH", new float[100]);

  AccY = cp5.addChart("AccY")
    .setPosition(50, 30)
    .setSize(400, 200)
    .setRange(-1, 1)
    .setView(Chart.LINE)
    .setStrokeWeight(4)
    .setColorCaptionLabel(color(40));
  AccY.addDataSet("AccY");
  AccY.setData("AccY", new float[100]);

  AccX = cp5.addChart("AccX")
    .setPosition(50, 330)
    .setSize(400, 200)
    .setRange(-1, 1)
    .setView(Chart.LINE)
    .setStrokeWeight(4)
    .setColorCaptionLabel(color(40));
  AccX.addDataSet("AccX");
  AccX.setData("AccX", new float[100]);

  AccZ = cp5.addChart("AccZ")
    .setPosition(50, 680)
    .setSize(400, 200)
    .setRange(-20, 20)
    .setView(Chart.LINE)
    .setStrokeWeight(4)
    .setColorCaptionLabel(color(40));
  AccZ.addDataSet("AccZ");
  AccZ.setData("AccZ", new float[100]);
 
  initFileWriter();
}
void draw() {
  hint(ENABLE_DEPTH_TEST);
  pushMatrix();
  
  roll.push("ROLL", smoothedEuler[2]);
  pitch.push("PITCH", smoothedEuler[1]);
  AccY.push("AccY", Acc[0]);
  AccX.push("AccX", Acc[1]);
  AccZ.push("AccZ", Acc[2]);
  background(204, 255, 255);
  
  drawSun(width / 2 + 400, height/2, 30, map(lightValue, 0, 500, 30, 200));
  checkForEarthquake();
  lights();
  ambientLight(102, 102, 102);
  translate(width / 2, height/2, 300);
  rotateZ(180 * PI / 180);
  
  rotateZ(-smoothedEuler[2] * PI / 180);
  rotateY(-smoothedEuler[0] * PI / 180 );
  rotateX(smoothedEuler[1] * PI / 180);
  shape(rocket);
  saveDataToFile();
  popMatrix();
  hint(DISABLE_DEPTH_TEST);
}

void receive(byte[] data, String ip, int port) {
  data = subset(data, 0, data.length);
  String message = new String(data);
  String[] list = split(message, ',');//Split the data using commas
  //Array for accelerometer data
  Acc[0] = Float.parseFloat(list[0]);
  Acc[1] = Float.parseFloat(list[1]);
  Acc[2] = Float.parseFloat(list[2]);
  
  lightValue = Float.parseFloat(list[3]);
  
  Euler[0] = Float.parseFloat(list[4]);
  Euler[1] = Float.parseFloat(list[5]);
  Euler[2] = Float.parseFloat(list[6]);
  
  for (int i = 0; i < 3; i++) {
    smoothedEuler[i] = smoothedEuler[i] * (1.0 - smoothingFactor) + Euler[i] * smoothingFactor;
  }
  println("receive: \"" + message + "\" from " + ip + " on port " + port);
}

void checkForEarthquake() {
  if (abs(Acc[0]) > ILSAsenstivity || abs(Acc[1]) > ILSAsenstivity) {
      println("Earthquake detected!");
  }
}

void drawSun(float x, float y, float sunRadius, float raysRadius) {
  noStroke();
  fill(255, 255, 0);
  ellipse(x, y, sunRadius * 2, sunRadius * 2);
  int numRays = 12; 
  float angleIncrement = TWO_PI / numRays;
  for (int i = 0; i < numRays; i++) {
    float angle = i * angleIncrement;
    float rayX = x + cos(angle) * raysRadius;
    float rayY = y + sin(angle) * raysRadius;
    stroke(255, 255, 0, 100); 
    line(x, y, rayX, rayY);
  }
  fill(0);
  textSize(15);
  text("LUX", x, y - 15);
  textSize(24);
  textAlign(CENTER, CENTER);  
  text(int(lightValue), x, y);
}

void initFileWriter() {
  String timestamp = nf(year(), 4) + nf(month(), 2) + nf(day(), 2) + nf(hour(), 2) + nf(minute(), 2) + nf(second(), 2);
  String fileName = "Lander_Data_" + timestamp + ".txt";
  dataWriter = createWriter(fileName);
}
void saveDataToFile() {
  String timestamp = nf(hour(), 2) + ":" + nf(minute(), 2) + ":" + nf(second(), 2);
  String dataLine = timestamp + "," + Acc[0] + "," + Acc[1] + "," + Acc[2] + "," + lightValue + "," + Euler[0] + "," + Euler[1] + "," + Euler[2];
  dataWriter.println(dataLine);
  dataWriter.flush();
}
