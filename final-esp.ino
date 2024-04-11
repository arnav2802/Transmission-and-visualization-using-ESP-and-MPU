#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>


const char* ssid = "SSID_NAME";
const char* password = "SSID_PASSWORD";
const char* udpServerIP = "DEVICE_IP";
const int udpServerPort = 6000;
WiFiUDP Udp;

Adafruit_MPU6050 mpu;

void setup() {
  Serial.begin(9600);


  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");


  Serial.println("Initializing MPU6050...");
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);

  Serial.println("MPU6050 initialized");
  Udp.begin(udpServerPort);
  delay(10);
}

void loop() {
  // Get sensor data
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


  String sensorData = String(a.acceleration.x) +"," + String(a.acceleration.y) +
                     "," + String(a.acceleration.z) + "," + "0"
                     "," + String(g.gyro.x) +
                     "," + String(g.gyro.y) +
                     "," + String(g.gyro.z);

  
  Udp.beginPacket(udpServerIP, udpServerPort);
  Udp.write(sensorData.c_str());
  Udp.endPacket();

 
  Serial.println(sensorData);

  delay(5); 
}