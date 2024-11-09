#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Wi-Fi Configuration
const char* primarySSID = "Your_WiFi_SSID";        // Replace with your Wi-Fi network SSID
const char* primaryPassword = "Your_WiFi_Password"; // Replace with your Wi-Fi network password

// Web Server Setup
ESP8266WebServer server(80);

// Disruption Detection and Access Control
volatile int disruptionPackets = 0;
const int disruptionThreshold = 10; // Threshold for triggering alert (number of deauth packets)
const int proximityRSSI = -70;       // RSSI threshold for device proximity control
int ledPin = D4;                    // LED for alert notifications

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Connect to Wi-Fi
  WiFi.begin(primarySSID, primaryPassword);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to primary network!");

  // Set up Web Server
  server.on("/", handleRoot);
  server.begin();
  Serial.println("Web server started!");

  // Enable Promiscuous Mode for Disruption Detection
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1);
  wifi_set_promiscuous_rx_cb(promiscuousCallback);
}

void promiscuousCallback(uint8_t* buf, uint16_t len) {
  // Detect disruption packets (Type 0xC0 for deauth frames)
  if (buf[0] == 0xC0) {
    disruptionPackets++;
  }
}

void handleRoot() {
  String html = "<html><head><title>Wi-Fi Access Control & Alert</title></head><body>";
  html += "<h1>Wi-Fi Network Disruption Alert with Location-Based Access Control</h1>";
  html += "<p>Disruption Packets Detected: " + String(disruptionPackets) + "</p>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void controlAccessBasedOnProximity() {
  int rssi = WiFi.RSSI(); // Measure signal strength for proximity

  if (rssi < proximityRSSI) {
    Serial.println("Device outside proximity - Restricting Access");
    WiFi.disconnect();   // Disconnect if outside proximity range
    delay(1000);         // Allow reconnect
  } else {
    Serial.println("Device within proximity - Access allowed");
  }
}

void alertDisruption() {
  Serial.println("Alert: Network Disruption Detected!");
  // Flash LED as an alert
  digitalWrite(ledPin, HIGH);
  delay(500);
  digitalWrite(ledPin, LOW);
}

void loop() {
  server.handleClient();

  // Check for disruption packets and proximity-based access control
  if (disruptionPackets >= disruptionThreshold) {
    alertDisruption();
    disruptionPackets = 0;  // Reset counter
  }
  
  controlAccessBasedOnProximity(); // Enforce location-based access

  delay(1000); // Check every second
}
