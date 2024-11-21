#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

// Replace with your Wi-Fi credentials
const char* ssid = "M-TECH";
const char* password = "Menywa4004";

// Set up the LED pin (GPIO15 for D8 on NodeMCU)
#define doorone 15
#define doortwo 12
#define doorthree 13
#define doorfour 14
#define doorfive 2

int digitalPin = 5;

ESP8266WebServer server(9000);

void setup() {
  // Start Serial Monitor
  Serial.begin(9600);
  EEPROM.begin(512); // Initialize EEPROM with 512 bytes
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected to WiFi");

  // Print the IP address
  Serial.print("ESP8266 IP Address: ");
  Serial.println(WiFi.localIP());

  // Initialize LED pin
  pinMode(doorone, OUTPUT);
  pinMode(doortwo, OUTPUT);
  pinMode(doorthree, OUTPUT);
  pinMode(doorfour, OUTPUT);
  pinMode(doorfive, OUTPUT);
  pinMode(digitalPin, INPUT);

  // Read saved state from EEPROM doorone
  int savedStatedoorone = EEPROM.read(0);
  if (savedStatedoorone == 1) {
    digitalWrite(doorone, HIGH);
    Serial.println("Pin set to HIGH from EEPROM.");
  } else {
    digitalWrite(doorone, LOW);
    Serial.println("Pin set to LOW from EEPROM.");
  }

  // Read saved state from EEPROM doortwo
  int savedStatedoortwo = EEPROM.read(0);
  if (savedStatedoortwo == 1) {
    digitalWrite(doortwo, HIGH);
    Serial.println("Pin set to HIGH from EEPROM.");
  } else {
    digitalWrite(doortwo, LOW);
    Serial.println("Pin set to LOW from EEPROM.");
  }

  // Read saved state from EEPROM doorthree
  int savedStatedoorthree = EEPROM.read(0);
  if (savedStatedoorthree == 1) {
    digitalWrite(doorthree, HIGH);
    Serial.println("Pin set to HIGH from EEPROM.");
  } else {
    digitalWrite(doorthree, LOW);
    Serial.println("Pin set to LOW from EEPROM.");
  }

  // Read saved state from EEPROM doorfour
  int savedStatedoorfour = EEPROM.read(0);
  if (savedStatedoorfour == 1) {
    digitalWrite(doorfour, HIGH);
    Serial.println("Pin set to HIGH from EEPROM.");
  } else {
    digitalWrite(doorfour, LOW);
    Serial.println("Pin set to LOW from EEPROM.");
  }

  // Read saved state from EEPROM doorfive
  int savedStatedoorfive = EEPROM.read(0);
  if (savedStatedoorfive == 1) {
    digitalWrite(doorfive, HIGH);
    Serial.println("Pin set to HIGH from EEPROM.");
  } else {
    digitalWrite(doorfive, LOW);
    Serial.println("Pin set to LOW from EEPROM.");
  }


   // Define routes FOR FIRST DOOR
  server.on("/highdoorone", []() {
    digitalWrite(doorone, HIGH);
    EEPROM.write(0, 1); // Save HIGH state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"HIGH\"}");
    Serial.println("Pin set to HIGH");
  });

  server.on("/lowdoorone", []() {
    digitalWrite(doorone, LOW);
    EEPROM.write(0, 0); // Save LOW state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"LOW\"}");
    Serial.println("Pin set to LOW");
  });

  // Define routes FOR TWO DOOR
  server.on("/highdoortwo", []() {
    digitalWrite(doortwo, HIGH);
    EEPROM.write(0, 1); // Save HIGH state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"HIGH\"}");
    Serial.println("Pin set to HIGH");
  });

  server.on("/lowdoortwo", []() {
    digitalWrite(doortwo, LOW);
    EEPROM.write(0, 0); // Save LOW state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"LOW\"}");
    Serial.println("Pin set to LOW");
  });

  // Define routes FOR THREE DOOR
  server.on("/highdoorthree", []() {
    digitalWrite(doorthree, HIGH);
    EEPROM.write(0, 1); // Save HIGH state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"HIGH\"}");
    Serial.println("Pin set to HIGH");
  });

  server.on("/lowdoorthree", []() {
    digitalWrite(doorthree, LOW);
    EEPROM.write(0, 0); // Save LOW state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"LOW\"}");
    Serial.println("Pin set to LOW");
  });

  // Define routes FOR FOUR DOOR
  server.on("/highdoorfour", []() {
    digitalWrite(doorfour, HIGH);
    EEPROM.write(0, 1); // Save HIGH state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"HIGH\"}");
    Serial.println("Pin set to HIGH");
  });

  server.on("/lowdoorfour", []() {
    digitalWrite(doorfour, LOW);
    EEPROM.write(0, 0); // Save LOW state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"LOW\"}");
    Serial.println("Pin set to LOW");
  });

  // Define routes FOR FIVE DOOR
  server.on("/highdoorfive", []() {
    digitalWrite(doorfive, HIGH);
    EEPROM.write(0, 1); // Save HIGH state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"HIGH\"}");
    Serial.println("Pin set to HIGH");
  });

  server.on("/lowdoorfive", []() {
    digitalWrite(doorfive, LOW);
    EEPROM.write(0, 0); // Save LOW state to EEPROM
    EEPROM.commit();
    server.send(200, "application/json", "{\"state\": \"LOW\"}");
    Serial.println("Pin set to LOW");
  });








  // Define the route for serving sensor data
  server.on("/get_data", []() {
    int analogValue = analogRead(digitalPin); // Read analog value
    int digitalValue = digitalRead(digitalPin); // Read digital value
    String state = (digitalValue == HIGH || analogValue > 512) ? "HIGH" : "LOW"; // Threshold for analog

    String jsonResponse = "{\"state\": \"" + state + "\"}";
    server.send(200, "application/json", jsonResponse); // Send JSON response
  });

  // Define routes
//  server.on("/web/on", HTTP_GET, []() {
//    digitalWrite(PIN, HIGH); // Turn LED on
//    server.send(200, "text/plain", "LED On");
//  });

//  server.on("/web/off", HTTP_GET, []() {
//    digitalWrite(LED_PIN, LOW);  // Turn LED off
//    server.send(200, "text/plain", "LED Off");
//  });

  // Start server
  server.begin(); // Start the server
  Serial.println("Server started");
}

void loop() {
  server.handleClient();  // Handle HTTP requests
}
