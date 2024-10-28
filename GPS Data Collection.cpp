#include <SoftwareSerial.h>
#include <TinyGPS++.h>

TinyGPSPlus gps;
SoftwareSerial gpsSerial(4, 3); // RX, TX for GPS module

void setup() {
  Serial.begin(9600);          // For serial monitoring
  gpsSerial.begin(9600);       // GPS module baud rate
}

void loop() {
  while (gpsSerial.available() > 0) {
    if (gps.encode(gpsSerial.read())) {
      if (gps.location.isUpdated()) {
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();

        Serial.print("Latitude: ");
        Serial.println(latitude, 6);
        Serial.print("Longitude: ");
        Serial.println(longitude, 6);

        // You can call a function here to send data over GSM module
        sendDataToServer(latitude, longitude);
      }
    }
  }
}
