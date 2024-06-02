// Libraries
#include <SoftwareSerial.h>

// Define software serial pins for Bluetooth module
SoftwareSerial bluetooth(2, 3); // RX, TX

// Define relay pin
const int relayPin = 8;

// Variable to store the data received from the Bluetooth module
char dataReceived = '0'; // Initialize with '0' (relay off)

void setup() {
  // Initialize serial communication for debugging
  Serial.begin(9600);
  while (!Serial);

  // Initialize Bluetooth serial communication
  bluetooth.begin(9600);

  // Set relay pin as output
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Ensure relay is initially off

  // Wait for the Bluetooth module to be ready
  delay(1000);
  Serial.println("Bluetooth module is ready");
}

void loop() {
  // Check if data is available from Bluetooth module
  while (bluetooth.available() > 0) {
    // Read the incoming data
    dataReceived = bluetooth.read();

    // Check if the received data is '1' or '0'
    if (dataReceived == '1') {
      digitalWrite(relayPin, HIGH); // Activate the relay
      Serial.println("Relay activated");
    } else if (dataReceived == '0') {
      digitalWrite(relayPin, LOW); // Deactivate the relay
      Serial.println("Relay deactivated");
    } else {
      Serial.println("Invalid data received");
    }
  }

  // Check if data is available from Serial monitor for debugging
  if (Serial.available()) {
    char debugData = Serial.read();
    if (debugData == '1') {
      digitalWrite(relayPin, HIGH); // Activate the relay
      bluetooth.write('1'); // Send feedback to Bluetooth module
      Serial.println("Relay activated via Serial");
    } else if (debugData == '0') {
      digitalWrite(relayPin, LOW); // Deactivate the relay
      bluetooth.write('0'); // Send feedback to Bluetooth module
      Serial.println("Relay deactivated via Serial");
    } else {
      Serial.println("Invalid command via Serial");
    }
  }

  // Add a small delay to prevent high CPU usage
  delay(10);
}
