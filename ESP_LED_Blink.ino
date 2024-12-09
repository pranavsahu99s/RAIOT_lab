#include <ESP8266WiFi.h>  // Include the ESP8266 Wi-Fi library

// Replace with your network credentials
const char* ssid = "your_SSID";     // Your Wi-Fi SSID (network name)
const char* password = "your_PASSWORD"; // Your Wi-Fi password

void setup() {
  // Start serial communication for debugging
  Serial.begin(115200);
  delay(10);

  // Connecting to Wi-Fi
  Serial.println();
  Serial.print("Connecting to WiFi...");
  
  WiFi.begin(ssid, password);  // Start the Wi-Fi connection
  
  // Wait for the connection to establish
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);  // Wait for 1 second
    Serial.print(".");
  }

  // Once connected, print the IP address
  Serial.println("");
  Serial.println("WiFi connected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // Print the ESP8266's IP address
}

void loop() {
  // You can add any code here that you want to run after connecting to Wi-Fi.
  // For now, we'll just blink the onboard LED every second.

  int ledPin = 2;  // Onboard LED is connected to GPIO2 (D4 on NodeMCU)
  pinMode(ledPin, OUTPUT);
  
  // Blink the LED every second
  digitalWrite(ledPin, HIGH);  // Turn LED on
  delay(1000);                  // Wait for 1 second
  digitalWrite(ledPin, LOW);   // Turn LED off
  delay(1000);                  // Wait for 1 second
}
