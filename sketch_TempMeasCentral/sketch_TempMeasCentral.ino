#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Preferences.h>

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
//funguje

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
double temperatures[10];
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

  ads.setGain(GAIN_ONE);

  if (!ads.begin())
  {
    Serial.println("Failed to initialize ADS.");
    while (1);
  }

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
    readAnalog();
  displayTemperatures();
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


void readAnalog()
{
  int16_t adc0, adc1, adc2, adc3;
  float volts0, volts1, volts2, volts3;
  adc0 = ads.readADC_SingleEnded(0);
  adc1 = ads.readADC_SingleEnded(1);
  //adc2 = ads.readADC_SingleEnded(2);
  //adc3 = ads.readADC_SingleEnded(3);
 
  volts0 = ads.computeVolts(adc0);
  volts1 = ads.computeVolts(adc1);

  temperatures[8] = voltageToTemperature(volts0);
  temperatures[9] = voltageToTemperature(volts1);
  //volts2 = ads.computeVolts(adc2);
  //volts3 = ads.computeVolts(adc3);

  //  Serial.println("-----------------------------------------------------------");
  // Serial.print("AIN0: "); Serial.print(adc0); Serial.print("  "); Serial.print(volts0); Serial.println("V");
  // Serial.print("AIN1: "); Serial.print(adc1); Serial.print("  "); Serial.print(volts1); Serial.println("V");
  // Serial.print("AIN2: "); Serial.print(adc2); Serial.print("  "); Serial.print(volts2); Serial.println("V");
  // Serial.print("AIN3: "); Serial.print(adc3); Serial.print("  "); Serial.print(volts3); Serial.println("V");

}

double voltageToTemperature(float volts)
{
  return 10.0 * volts;
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
  temperatureString += ";" + String(lastPulseTime1);
  temperatureString += ";" + String(lastPulseTime2);
  Serial.println(temperatureString);
}
//551189319;0

void showSetup()
{
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_te);
  u8g2.setCursor(0, 30);
  u8g2.print("SETUP");
  u8g2.sendBuffer();
}


void displayTemperatures() {
  u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFont(  u8g2_font_timR08_tr);

  int fl = 10;
  int lh = 12;
  int y = fl;

  u8g2.setCursor(0, y);
  u8g2.print("T1: "); u8g2.print(temperatures[0]); u8g2.print(" C");

  
  u8g2.setCursor(64, y);
  u8g2.print("T5: "); u8g2.print(temperatures[4]); u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T2: "); u8g2.print(temperatures[1]); u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("T6: "); u8g2.print(temperatures[5]); u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T3: "); u8g2.print(temperatures[2]); u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("T9: "); u8g2.print(temperatures[8]); u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T4: "); u8g2.print(temperatures[3]); u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("TA: "); u8g2.print(temperatures[9]); u8g2.print(" C");

  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("Vt: "); u8g2.print(550); u8g2.print(" l/h");

  u8g2.setCursor(64, y);
  u8g2.print("P: "); u8g2.print(1000); u8g2.print(" W");

  u8g2.sendBuffer();
}

