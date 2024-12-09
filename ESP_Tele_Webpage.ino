#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClientSecure.h>
#include <ESP8266HTTPClient.h>

// WiFi credentials
const char* ssid = "ssid";
const char* password = "pswd";

// Telegram bot credentials
const String BOT_TOKEN = "tele_bot_token";
const String CHAT_ID = "_tele_chat_id_";

// Web server on port 80
ESP8266WebServer server(80);

// Function to send a message to Telegram
void sendToTelegram(String message) {
  WiFiClientSecure client;  // Use secure client for HTTPS
  client.setInsecure();     // Disable certificate validation (simplifies setup)

  HTTPClient https;         // Create HTTPS client

  // Encode the message for URL
  message.replace(" ", "%20");

  // Telegram API URL
  String url = "https://api.telegram.org/bot" + BOT_TOKEN + "/sendMessage?chat_id=" + CHAT_ID + "&text=" + message;

  Serial.println("Sending message to Telegram...");
  Serial.println("Request URL: " + url);

  if (https.begin(client, url)) { // Connect to Telegram
    int httpCode = https.GET();  // Send the GET request

    // Print the HTTP response code and body
    Serial.println("HTTP Response code: " + String(httpCode));
    if (httpCode > 0) {
      String payload = https.getString();
      Serial.println("Response: " + payload);
    } else {
      Serial.println("Error sending message to Telegram. HTTP error code: " + String(httpCode));
    }
    https.end();  // Close the connection
  } else {
    Serial.println("Failed to connect to Telegram API.");
  }
}

// Function to handle the root webpage
void handleRoot() {
  String html = "<!DOCTYPE html><html lang='en'><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>Send Message to Telegram</title></head><body>";
  html += "<h1>Send a Message to Telegram Bot</h1>";
  html += "<form action='/send' method='POST'>";
  html += "<label for='message'>Message:</label><br>";
  html += "<input type='text' id='message' name='message' required><br><br>";
  html += "<input type='submit' value='Send'>";
  html += "</form></body></html>";
  
  server.send(200, "text/html", html);
}

// Function to handle sending a message
void handleSend() {
  if (server.hasArg("message")) {
    String message = server.arg("message");
    sendToTelegram(message);
    server.send(200, "text/html", "Message sent to Telegram! <a href='/'>Back</a>");
  } else {
    server.send(400, "text/html", "Message not received! <a href='/'>Back</a>");
  }
}

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected! IP address: " + WiFi.localIP().toString());

  // Start the web server
  server.on("/", handleRoot);
  server.on("/send", HTTP_POST, handleSend);
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  server.handleClient();  // Handle incoming HTTP requests
}
