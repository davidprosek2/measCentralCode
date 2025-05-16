#include <U8g2lib.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Preferences.h>

#include <Adafruit_ADS1X15.h>
Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
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
double temperatures[16];
double flow;
Preferences preferences;

int pulsePin1 = 26;


volatile unsigned long lastPulseTime1 = 0;
volatile unsigned long pulsePeriod1 = 0;
volatile unsigned long pulseCount1 = 0;


void IRAM_ATTR handlePulse1() {
  unsigned long currentTime = millis();
  //if((currentTime - lastPulseTime1) > 2)
  {
  pulsePeriod1 = currentTime - lastPulseTime1;
  lastPulseTime1 = currentTime;
  pulseCount1++;
  }
}



// Device addresses  
DeviceAddress sensor1 = { 0x28, 0x1C, 0x7C, 0x1B, 0x10, 0x00, 0x00, 0x92 };
DeviceAddress sensor2 = { 0x28, 0x7C, 0x59, 0x1C, 0x10, 0x00, 0x00, 0xFD };
DeviceAddress sensor3 = { 0x28, 0xA1, 0xF2, 0x1A, 0x10, 0x00, 0x00, 0x39 };
DeviceAddress sensor4 = { 0x28, 0x65, 0x53, 0x1C, 0x10, 0x00, 0x00, 0x8D };
DeviceAddress sensor5 = { 0x28, 0x10, 0x8F, 0x1C, 0x10, 0x00, 0x00, 0x81 };
DeviceAddress sensor6 = { 0x28, 0xCE, 0xA0, 0x1B, 0x10, 0x00, 0x00, 0x47 };
DeviceAddress sensor7 = { 0x28, 0xD0, 0x22, 0x5F, 0x10, 0x00, 0x00, 0xA9 };
DeviceAddress sensor8 = { 0x28, 0x86, 0xB9, 0x5E, 0x10, 0x00, 0x00, 0x7D };






U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/18, /* data=*/23, /* CS=*/5, /* reset=*/0);  // ESP32

//adc bude 21 a 22
// display reset bude 0 misto 22

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}


void processMessage(String str) {
  setupMode = false;
  str.trim();
  if (str == "PA") {
    printAllSensorsAddresses();
  } else if (str == "SETUP") {
    setupMode = true;
  }
  //else if(str.)
}

void setup() {
  u8g2.begin();
  Serial.begin(115200);
  sensors.begin();


  //InitSensorAddresses();

  //podsvícení
  pinMode(backligtPin, OUTPUT);
  analogWrite(backligtPin, 20);
  pulseCount1 = 0;

  //inicializace čítače
  pinMode(pulsePin1, INPUT);
  
  attachInterrupt(digitalPinToInterrupt(pulsePin1), handlePulse1, RISING);
  
}

unsigned long period1 ;
    unsigned long count1;
    unsigned long lastPulse;
    unsigned long lastPulseCount;
    unsigned long lastPulseCountTime;

void loop() {
  // Example temperatures

  if (setupMode) {
    showSetup();
  } else {
    noInterrupts();
     period1 = pulsePeriod1;
     count1 = pulseCount1;
     lastPulse = lastPulseTime1;
    interrupts();
    
//    flow = PeriodToFlow(period1);
unsigned long currentTime = millis();
  unsigned long pc = count1-lastPulseCount;
  unsigned long interval = (currentTime-lastPulseCountTime);
  float vol = PulsesToVolume(pc);
  float overallVol = PulsesToVolume(count1);
  flow = (vol/(float)interval)*60000*60;
   lastPulseCountTime = currentTime;
   lastPulseCount = count1;
   readTemperatures();
    temperatures[10] = flow;
    temperatures[9] = overallVol;
    
    displayTemperatures();
    sendTemperatures();
  }

  while (Serial.available()) {
    //char c = Serial.read();
    String str = Serial.readString();
    //Serial.println(str.c_str());
    processMessage(str);
  }

  delay(10000);  // Update every 2 seconds
  
  //if(currentTime - lastPulse > (60000 / 2))
  //  period1 = (currentTime - lastPulse)*4;
  /*if(currentTime - lastPulseTime2 > (60000 * 5))
    pulsePeriod2 = (currentTime - lastPulseTime2);*/

}

///
/// frekvence pulsu je 1puls na litr
///
float PeriodToFlow(unsigned long period)
{
  if(period == 0)
    return 0.0f;
  float freq = 1000.0f / (float)period;
  float flowi = (freq-8.0f)/6.0f*60.0f;
  if(flowi < 0.0)
    flowi = 0.0;
  return flowi;
}

float PulsesToVolume(unsigned long pulses)
{
  return (float)pulses/476.0f;
}

/// frekvence je puls na 50kJ 
float PeriodToPower(unsigned long period)
{
  if(period == 0)
    return 0.0;
  float freq = 1000.0 / (float)period;
  float PkW = 50 * freq;
 // if(PkW < 0.5)
   // PkW = 0;
  return PkW;
}

void printAllSensorsAddresses() {
  printAddress(sensor1);
  printAddress(sensor2);
  printAddress(sensor3);
  printAddress(sensor4);
  printAddress(sensor5);
  printAddress(sensor6);
  printAddress(sensor7);
  printAddress(sensor8);
}

// void InitSensorAddresses() {
//   preferences.begin("my_variables", false);
//   if (!preferences.getBool("initialized", false)) {
//     // Initializing the sensor addresses if not already done
//     preferences.putBytes("sensor1", sensor1, sizeof(DeviceAddress));
//     preferences.putBytes("sensor2", sensor2, sizeof(DeviceAddress));
//     preferences.putBytes("sensor3", sensor3, sizeof(DeviceAddress));
//     preferences.putBytes("sensor4", sensor4, sizeof(DeviceAddress));
//     preferences.putBytes("sensor5", sensor5, sizeof(DeviceAddress));
//     preferences.putBytes("sensor6", sensor6, sizeof(DeviceAddress));
//     preferences.putBytes("sensor7", sensor7, sizeof(DeviceAddress));
//     preferences.putBytes("sensor8", sensor8, sizeof(DeviceAddress));
//     preferences.putBool("initialized", true);
//   } else {
//     // Retrieve sensor addresses from non-volatile memory
//     preferences.getBytes("sensor1", sensor1, sizeof(DeviceAddress));
//     preferences.getBytes("sensor2", sensor2, sizeof(DeviceAddress));
//     preferences.getBytes("sensor3", sensor3, sizeof(DeviceAddress));
//     preferences.getBytes("sensor4", sensor4, sizeof(DeviceAddress));
//     preferences.getBytes("sensor5", sensor5, sizeof(DeviceAddress));
//     preferences.getBytes("sensor6", sensor6, sizeof(DeviceAddress));
//     preferences.getBytes("sensor7", sensor7, sizeof(DeviceAddress));
//     preferences.getBytes("sensor8", sensor8, sizeof(DeviceAddress));
//   }

//   preferences.end();
// }



void readTemperatures() {
  sensors.requestTemperatures();  // Send the command to get temperatures

  temperatures[0] = sensors.getTempC(sensor1,2);
  temperatures[1] = sensors.getTempC(sensor2,2);
  temperatures[2] = sensors.getTempC(sensor3,2);
  temperatures[3] = sensors.getTempC(sensor4,2);
  temperatures[4] = sensors.getTempC(sensor5,2);
  temperatures[5] = sensors.getTempC(sensor6,2);
  temperatures[6] = sensors.getTempC(sensor7,2);
  temperatures[7] = sensors.getTempC(sensor8,2);

  for(int i = 0;i<8;i++)
  {
    if(temperatures[i] < -100.0)
      temperatures[i] = 0.0;
  }

  
}

void printAddress(DeviceAddress deviceAddress) {
  for (uint8_t i = 0; i < 8; i++) {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
  Serial.print(":");
  if (sensors.isConnected(deviceAddress))
    Serial.print("Connected");
  else
    Serial.print("FAILED");
  Serial.println();
}

void sendTemperatures() {
  String temperatureString = String(millis()) ;
  for (int i = 0; i < 11; i++) {
    temperatureString += ";" + String(temperatures[i]);
  }

  

  Serial.println(temperatureString);
}
//551189319;0

void showSetup() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB14_te);
  u8g2.setCursor(0, 30);
  u8g2.print("SETUP");
  u8g2.sendBuffer();
}


void displayTemperatures() {
  u8g2.clearBuffer();
  //u8g2.setFont(u8g2_font_ncenB08_tr);
  u8g2.setFont(u8g2_font_timR08_tr);

  int fl = 10;
  int lh = 12;
  int y = fl;

  u8g2.setCursor(0, y);
  u8g2.print("T1: ");
  u8g2.print(temperatures[0]);
  u8g2.print(" C");


  u8g2.setCursor(64, y);
  u8g2.print("T5: ");
  u8g2.print(temperatures[4]);
  u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T2: ");
  u8g2.print(temperatures[1]);
  u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("T6: ");
  u8g2.print(temperatures[5]);
  u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T3: ");
  u8g2.print(temperatures[2]);
  u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("T7: ");
  u8g2.print(temperatures[6]);
  u8g2.print(" C");
  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("T4: ");
  u8g2.print(temperatures[3]);
  u8g2.print(" C");

  u8g2.setCursor(64, y);
  u8g2.print("T8: ");
  u8g2.print(temperatures[7]);
  u8g2.print(" C");

  y += lh;

  u8g2.setCursor(0, y);
  u8g2.print("Vt: ");
  char buffer10[10];
  dtostrf(flow, 4, 0, buffer10);
  u8g2.print(buffer10);
  u8g2.print(" l/h");

  u8g2.setCursor(64, y);
  u8g2.print("V: ");
  char buffer11[10];
  dtostrf(temperatures[9], 4, 0, buffer11);
  u8g2.print(buffer11);
  u8g2.print(" l");

  u8g2.sendBuffer();
}
