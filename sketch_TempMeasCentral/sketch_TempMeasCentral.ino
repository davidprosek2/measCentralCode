#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Preferences.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

// pokus git
#define ONE_WIRE_BUS 15


bool setupMode = false;
const int backligtPin = 4;

// Create a oneWire instance to communicate with any OneWire devices
OneWire oneWire(ONE_WIRE_BUS);

// Pass the oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);
double temperatures[8];
Preferences preferences;

int pulsePin1 = 25;
int pulsePin2 = 26;

volatile unsigned long lastPulseTime1 = 0;
volatile unsigned long pulsePeriod1 = 0;
volatile unsigned long pulseCount1 = 0;

volatile unsigned long lastPulseTime2 = 0;
volatile unsigned long pulsePeriod2 = 0;
volatile unsigned long pulseCount2 = 0;

void IRAM_ATTR handlePulse1() {
  unsigned long currentTime = micros();
  pulsePeriod1 = currentTime - lastPulseTime1;
  lastPulseTime1 = currentTime;
  pulseCount1++;
}

void IRAM_ATTR handlePulse2() {
  unsigned long currentTime = micros();
  pulsePeriod2 = currentTime - lastPulseTime2;
  lastPulseTime2 = currentTime;
  pulseCount2++;
}

// Device addresses
DeviceAddress sensor1 = { 0x28, 0x1C, 0x7C, 0x1B, 0x10, 0x00, 0x00, 0x92 };
DeviceAddress sensor2 = { 0x28, 0x7C, 0x59, 0x1C, 0x10, 0x00, 0x00, 0xFD };
DeviceAddress sensor3 = { 0x28, 0xA1, 0xF2, 0x1A, 0x10, 0x00, 0x00, 0x39 };
DeviceAddress sensor4 = { 0x28, 0x65, 0x53, 0x1C, 0x10, 0x00, 0x00, 0x8D };
DeviceAddress sensor5 = { 0x28, 0x10, 0x8F, 0x1C, 0x10, 0x00, 0x00, 0x81 };
DeviceAddress sensor6 = { 0x28, 0xCE, 0xA0, 0x1B, 0x10, 0x00, 0x00, 0x47 };
DeviceAddress sensor7 = { 0x28, 0x01, 0xD1, 0x1B, 0x10, 0x00, 0x00, 0x5C };
DeviceAddress sensor8 = { 0x28, 0xFF, 0x6B, 0x1A, 0x10, 0x00, 0x00, 0x40 };



U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 18, /* data=*/ 23, /* CS=*/ 5, /* reset=*/ 0); // ESP32

//adc bude 21 a 22
// display reset bude 0 misto 22

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}


void processMessage(String str)
{
  setupMode = false;
  str.trim();
  if(str == "PA")
  {
      printAllSensorsAddresses();
  }
  else if(str == "SETUP")
  {
      setupMode = true;
  }
  //else if(str.)
}

void setup() 
{
  u8g2.begin();
  Serial.begin(115200);
  sensors.begin();
   

  InitSensorAddresses();

  //podsvícení
  pinMode(backligtPin,OUTPUT);
  analogWrite(backligtPin,20);

  //inicializace čítače
  pinMode(pulsePin1, INPUT_PULLUP);
  pinMode(pulsePin2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePin1), handlePulse1, FALLING);
  attachInterrupt(digitalPinToInterrupt(pulsePin2), handlePulse2, FALLING);

  // Check each sensor and print the address
 

}

void loop() {
  // Example temperatures

  if(setupMode)
  {
      showSetup();
  }
else
{
  readTemperatures();
  displayTemperatures(temperatures[0], temperatures[1], temperatures[2], temperatures[3], temperatures[4], temperatures[5], temperatures[6], temperatures[7]);
  sendTemperatures();
    noInterrupts();
  unsigned long period1 = pulsePeriod1;
  unsigned long count1 = pulseCount1;
  unsigned long period2 = pulsePeriod2;
  unsigned long count2 = pulseCount2;
  interrupts();
}

  while (Serial.available()) 
  {
    //char c = Serial.read();
    String str = Serial.readString();
    //Serial.println(str.c_str());
   processMessage(str);
  }

  delay(2000); // Update every 2 seconds
}




void printAllSensorsAddresses()
{
   printAddress(sensor1);
  printAddress(sensor2);
  printAddress(sensor3);
  printAddress(sensor4);
  printAddress(sensor5);
  printAddress(sensor6);
  printAddress(sensor7);
  printAddress(sensor8);  
}

void InitSensorAddresses()
{
  preferences.begin("my_variables", false);
    if (!preferences.getBool("initialized", false)) {
    // Initializing the sensor addresses if not already done
    preferences.putBytes("sensor1", sensor1, sizeof(DeviceAddress));
    preferences.putBytes("sensor2", sensor2, sizeof(DeviceAddress));
    preferences.putBytes("sensor3", sensor3, sizeof(DeviceAddress));
    preferences.putBytes("sensor4", sensor4, sizeof(DeviceAddress));
    preferences.putBytes("sensor5", sensor5, sizeof(DeviceAddress));
    preferences.putBytes("sensor6", sensor6, sizeof(DeviceAddress));
    preferences.putBytes("sensor7", sensor7, sizeof(DeviceAddress));
    preferences.putBytes("sensor8", sensor8, sizeof(DeviceAddress));
    preferences.putBool("initialized", true);
  } else {
    // Retrieve sensor addresses from non-volatile memory
    preferences.getBytes("sensor1", sensor1, sizeof(DeviceAddress));
    preferences.getBytes("sensor2", sensor2, sizeof(DeviceAddress));
    preferences.getBytes("sensor3", sensor3, sizeof(DeviceAddress));
    preferences.getBytes("sensor4", sensor4, sizeof(DeviceAddress));
    preferences.getBytes("sensor5", sensor5, sizeof(DeviceAddress));
    preferences.getBytes("sensor6", sensor6, sizeof(DeviceAddress));
    preferences.getBytes("sensor7", sensor7, sizeof(DeviceAddress));
    preferences.getBytes("sensor8", sensor8, sizeof(DeviceAddress));
  }
  
  preferences.end();
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
  // for (int i = 0; i < 8; i++) {
  //   Serial.print("Sensor ");
  //   Serial.print(i + 1);
  //   Serial.print(": ");
  //   Serial.print(temperatures[i]);
  //   Serial.println(" °C");
  // }
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.print(":");
  if(sensors.isConnected(deviceAddress))
    Serial.print("Connected");
  else
   Serial.print("FAILED");
  Serial.println();
}

void sendTemperatures() {
  String temperatureString = String(temperatures[0]);
  for (int i = 1; i < 8; i++) {
    temperatureString += ";" + String(temperatures[i]);
  }
  Serial.println(temperatureString);
}


void showSetup()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_te);
  u8g2.setCursor(0, 30);
  u8g2.print("SETUP");
  u8g2.sendBuffer();
}


void displayTemperatures(double temp1, double temp2, double temp3, double temp4,
                         double temp5, double temp6, double temp7, double temp8) {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  u8g2.setCursor(0, 10);
  u8g2.print("T1: "); u8g2.print(temp1); u8g2.print(" C");

  u8g2.setCursor(64, 10);
  u8g2.print("T5: "); u8g2.print(temp5); u8g2.print(" C");

  u8g2.setCursor(0, 26);
  u8g2.print("T2: "); u8g2.print(temp2); u8g2.print(" C");

  u8g2.setCursor(64, 26);
  u8g2.print("T6: "); u8g2.print(temp6); u8g2.print(" C");

  u8g2.setCursor(0, 42);
  u8g2.print("T3: "); u8g2.print(temp3); u8g2.print(" C");

  u8g2.setCursor(64, 42);
  u8g2.print("T7: "); u8g2.print(temp7); u8g2.print(" C");

  u8g2.setCursor(0, 58);
  u8g2.print("T4: "); u8g2.print(temp4); u8g2.print(" C");

  u8g2.setCursor(64, 58);
  u8g2.print("T8: "); u8g2.print(temp8); u8g2.print(" C");

  u8g2.sendBuffer();
}

