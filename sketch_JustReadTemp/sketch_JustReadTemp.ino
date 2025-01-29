#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is connected to pin 2 on the Arduino
#define ONE_WIRE_BUS 15

// Create a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

// Array to hold temperature readings
double temperatures[8];

// Device addresses
DeviceAddress sensor1 = { 0x28, 0x1C, 0x7C, 0x1B, 0x10, 0x00, 0x00, 0x92 };
DeviceAddress sensor2 = { 0x28, 0x7C, 0x59, 0x1C, 0x10, 0x00, 0x00, 0xFD };
DeviceAddress sensor3 = { 0x28, 0xA1, 0xF2, 0x1A, 0x10, 0x00, 0x00, 0x39 };
DeviceAddress sensor4 = { 0x28, 0x65, 0x53, 0x1C, 0x10, 0x00, 0x00, 0x8D };
DeviceAddress sensor5 = { 0x28, 0x10, 0x8F, 0x1C, 0x10, 0x00, 0x00, 0x81 };
DeviceAddress sensor6 = { 0x28, 0xCE, 0xA0, 0x1B, 0x10, 0x00, 0x00, 0x47 };
DeviceAddress sensor7 = { 0x28, 0x01, 0xD1, 0x1B, 0x10, 0x00, 0x00, 0x5C };
DeviceAddress sensor8 = { 0x28, 0xFF, 0x6B, 0x1A, 0x10, 0x00, 0x00, 0x40 };

void setup() {
  Serial.begin(115200);
  sensors.begin();

  // Check each sensor and print the address
  printAddress(sensor1);
  printAddress(sensor2);
  printAddress(sensor3);
  printAddress(sensor4);
  printAddress(sensor5);
  printAddress(sensor6);
  printAddress(sensor7);
  printAddress(sensor8);
}

void loop() {
  readTemperatures();
  delay(2000); // Delay in milliseconds
}

void readTemperatures() {
  sensors.requestTemperatures(); // Send the command to get temperatures

  temperatures[0] = sensors.getTempC(sensor1);
  temperatures[1] = sensors.getTempC(sensor2);
  temperatures[2] = sensors.getTempC(sensor3);
  temperatures[3] = sensors.getTempC(sensor4);
  temperatures[4] = sensors.getTempC(sensor5);
  temperatures[5] = sensors.getTempC(sensor6);
  temperatures[6] = sensors.getTempC(sensor7);
  temperatures[7] = sensors.getTempC(sensor8);

  // Print temperatures to Serial Monitor
  for (int i = 0; i < 8; i++) {
    Serial.print("Sensor ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(temperatures[i]);
    Serial.println(" °C");
  }
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.println();
}
