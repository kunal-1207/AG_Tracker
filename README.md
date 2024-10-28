# Arduino GPS Tracker with Google Maps
A GPS tracking system built with Arduino, GPS, and GSM modules to send real-time location data to a server, which then displays it on Google Maps for live tracking.

## Table of Contents
1. Overview
2. Hardware Requirements
3. Software Requirements
4. Installation & Setup
5. Code Snippets
6. Usage


## Overview
The Arduino GPS Tracker collects GPS coordinates using the Neo-6M GPS module, transmits them to a server via a GSM module, and displays real-time location on Google Maps using a web interface.

## Hardware Requirements
- Arduino (e.g., Uno or Mega)
- Neo-6M GPS Module
- SIM800L or SIM900 GSM Module
- Battery or Power Supply

## Software Requirements
- Arduino IDE (with the TinyGPSPlus library)
- Node.js (for server-side code)
- Google Maps API Key

## Installation & Setup
#### Step 1: Hardware Connections
1. GPS Module: Connect TX to D4 and RX to D3 on the Arduino.
2. GSM Module: Connect TX to D2 and RX to D1 on the Arduino.

#### Step 2: Server Setup

1. Install Node.js and Express:

       npm init -y
       npm install express

2. Add server.js (below) in the project directory, then start the server:

       node server.js

#### Step 3: Google Maps API Key
Get a key from Google Cloud Console and add it to map.html.

Code Snippets
1. Arduino GPS Data Collection and GSM Transmission
This code collects GPS data from the Neo-6M module and sends it to the server via GSM.

       #include <SoftwareSerial.h>
       #include <TinyGPS++.h>

       TinyGPSPlus gps;
       SoftwareSerial gpsSerial(4, 3);    // GPS Module
       SoftwareSerial gsmSerial(2, 1);    // GSM Module

       void setup() {
         Serial.begin(9600);
         gpsSerial.begin(9600);
         gsmSerial.begin(9600);
       }

       void loop() {
         while (gpsSerial.available() > 0) {
               if (gps.encode(gpsSerial.read()) && gps.location.isUpdated()) {
               float lat = gps.location.lat();
               float lng = gps.location.lng();
               sendDataToServer(lat, lng);
                        }
                     }
                 }

        void sendDataToServer(float lat, float lng) {
                 String url = "http://your-server-url.com/update-location?lat=" + String(lat, 6) + "&lng=" + String(lng, 6);
                 gsmSerial.println("AT+HTTPINIT");
                 delay(1000);
                 gsmSerial.println("AT+HTTPPARA=\"URL\",\"" + url + "\"");
                 delay(1000);
                 gsmSerial.println("AT+HTTPACTION=0");
                 delay(5000);
                }


2. Server-Side Code (Node.js with Express)
This server logs GPS coordinates received from Arduino and makes them available to the web map.

        // server.js
       const express = require('express');
       const app = express();
       const port = 3000;

       app.get('/update-location', (req, res) => {
        const { lat, lng } = req.query;
       if (lat && lng) {
        console.log(`Latitude: ${lat}, Longitude: ${lng}`);
        res.send('GPS Data Received');
       } else {
        res.status(400).send('Invalid Data');
        }
       });

         app.listen(port, () => console.log(`Server at http://localhost:${port}`));

3. Google Maps Visualization (HTML)
Displays the location on Google Maps using the GPS data from the server. Replace YOUR_API_KEY.


        <!DOCTYPE html>
        <html>
        <head>
          <title>GPS Tracker Map</title>
          <script src="https://maps.googleapis.com/maps/api/js?key=YOUR_API_KEY"></script>
          <style>#map { height: 500px; width: 100%; }</style>
        </head>
        <body>
            <div id="map"></div>
            <script>
                function initMap(latitude = 37.7749, longitude = -122.4194) {
                  const map = new google.maps.Map(document.getElementById('map'), {
                    zoom: 15, center: { lat: latitude, lng: longitude }
                  });
                  const marker = new google.maps.Marker({ map: map, position: { lat: latitude, lng: longitude } });
            
                  setInterval(() => {
                    fetch('http://localhost:3000/latest-location')
                      .then(response => response.json())
                      .then(data => {
                        marker.setPosition({ lat: parseFloat(data.lat), lng: parseFloat(data.lng) });
                        map.panTo(marker.getPosition());
                      });
                  }, 5000);
                }
                window.onload = initMap;
          </script>
        </body>
        </html>

##### Usage
1. Upload the Arduino code for GPS and GSM modules.
2. Run the server script with Node.js: node server.js.
3. Open map.html in a browser to see real-time GPS tracking.
   
##### License
This project is licensed under the MIT License.
