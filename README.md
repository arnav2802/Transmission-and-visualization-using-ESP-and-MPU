# Transmission-and-visualization-using-ESP-and-MPU

Real -Time Telemetry Avionic Data Transmission
This project transmits live telemetry data from avionic(MPU6050) sensor to a specified UDP server using an ESP8266 WiFi module. The data includes roll, pitch, acceleration in X, Y, and Z axes, and light value. The data is smoothed using a moving average filter and displayed in real-time using Processing.

**Features**

Live telemetry data transmission,
Uses ESP8266 WiFi module for communication,
MPU6050 sensor for data collection,
Smoothing of sensor data using a moving average filter,
Real-time display of data using Processing.

**Technologies Used**
ESP8266 WiFi module,
Processing,
UDP protocol,
Adafruit MPU6050 library.

**Setup**
To use this project, follow these steps:

Install the required libraries in the Arduino IDE.
Replace SSID_NAME and SSID_PASSWORD with your WiFi network credentials.
Replace DEVICE_IP with the IP address of the UDP server.
Upload the code to your ESP8266 board.

**License**
This project is licensed under the MIT License - see the LICENSE file for details.

**Contact**
If you have any questions or comments about this project, please contact me at arnav171103@gmail.com
