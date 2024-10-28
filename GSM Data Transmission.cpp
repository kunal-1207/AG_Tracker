SoftwareSerial gsmSerial(2, 1); // RX, TX for GSM module

void setup() {
  Serial.begin(9600);            // Serial monitor
  gsmSerial.begin(9600);         // GSM module
}

void sendDataToServer(float lat, float lng) {
  String url = "http://your-server-url.com/update-location?lat=";
  url += String(lat, 6);
  url += "&lng=";
  url += String(lng, 6);

  gsmSerial.println("AT+CSQ");               // Check signal strength
  delay(1000);
  gsmSerial.println("AT+HTTPINIT");          // Initialize HTTP service
  delay(1000);
  gsmSerial.println("AT+HTTPPARA=\"URL\",\"" + url + "\"");
  delay(1000);
  gsmSerial.println("AT+HTTPACTION=0");      // Start HTTP GET action
  delay(5000);                               // Wait for response

  Serial.println("Data sent to server: " + url);
}
