#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16

  const unsigned char logoBof [] PROGMEM = {
  0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0x00, 0x00, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0x00, 0x01, 0xf0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0x00, 0x1c, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0x00, 0x38, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0x00, 0x60, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x80, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0x1f, 0x80, 0x06, 0x00, 0x03, 0x8c, 0x84, 0x24, 0xcf, 0x78, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x31, 0x00, 0x06, 0x00, 0x02, 0x52, 0x84, 0x25, 0x28, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0x22, 0x00, 0x0c, 0x00, 0x03, 0x92, 0x84, 0x3d, 0x2e, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x64, 0x00, 0x18, 0x00, 0x02, 0x52, 0x84, 0x25, 0x28, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0x44, 0x00, 0x18, 0x00, 0x03, 0x8c, 0xf7, 0xa4, 0xc8, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x40, 0xc8, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xc0, 0xfc, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0c, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x38, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0xfc, 0x02, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x07, 0xfe, 0x0c, 0x80, 0x00, 0x11, 0x4a, 0x1f, 0x77, 0xde, 0x64, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x1f, 0xff, 0xf0, 0x80, 0x00, 0x1b, 0x4a, 0x04, 0x21, 0x10, 0x94, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x7f, 0xff, 0xa0, 0x80, 0x00, 0x15, 0x4a, 0x04, 0x21, 0x1c, 0x87, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0xa7, 0x00, 0x00, 0x11, 0x4a, 0x04, 0x21, 0x10, 0x94, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x3c, 0x00, 0x00, 0x11, 0x33, 0xc4, 0x71, 0x1e, 0x64, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xff, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const char* ssid = "";
const char* password = "";
  
volatile int flow_frequency; // Measures flow sensor pulses
unsigned int literByMin; // Calculated litres/min
unsigned char flowsensor = 12; // Sensor Input
unsigned long currentTime;
unsigned long cloopTime;
unsigned long serverTime;
int sensor_id=1;
int greenPin=13;
int redPin=15;
int mini=5;
int alert=8;
ICACHE_RAM_ATTR void flow () // Interrupt function
{
   flow_frequency++;
}
void setup()
{
   Serial.begin(9600);
   pinMode(flowsensor, INPUT);
   pinMode(redPin, OUTPUT);
   pinMode(greenPin, OUTPUT);
   attachInterrupt(digitalPinToInterrupt(flowsensor), flow, RISING); // Setup Interrupt
   sei(); // Enable interrupts
   currentTime = millis();
   cloopTime = currentTime;
   digitalWrite(redPin, HIGH);
   digitalWrite(greenPin, LOW);
   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)){ // Address 0x3C for 128x32
        Serial.println(("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
        }
   display.begin(SSD1306_SWITCHCAPVCC,0x3C);
   display.clearDisplay();
   display.drawBitmap(0, 0, logoBof, 128, 64, WHITE);
   display.display();
   WiFi.begin(ssid, password);
   while(WiFi.status() != WL_CONNECTED){
    delay(500);
   }
   delay(4000);
}
void loop ()
{
   currentTime = millis();
   // Every second, calculate and print litres/hour
   if(currentTime >= (cloopTime + 1000))
   {
      
      cloopTime = currentTime; // Updates cloopTime
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      literByMin = (flow_frequency/ 7.5); // 
      
      Serial.println(literByMin);
      flow_frequency = 0; // Reset Counter
      if(literByMin<mini){
        digitalWrite(redPin, HIGH);
        digitalWrite(greenPin, LOW);
      }else if(literByMin<alert){
        analogWrite(redPin, 255);
        analogWrite(greenPin, 100);
      }else{
        digitalWrite(redPin, LOW);
        digitalWrite(greenPin, HIGH);
      }
   }

   if(currentTime >= (serverTime + 10000)){
    serverTime = currentTime;
    sendToServer(literByMin);
    updateFromServer();
   }
   displayToLcd(literByMin,mini,alert);
   
}

void sendToServer(int literByMin){
  if (WiFi.status() == WL_CONNECTED){
    Serial.println("connecté");
    HTTPClient http;
    http.begin("http://192.168.1.25:8000/post/");
    http.addHeader("Content-type", "application/x-www-form-urlencoded");
    String sensorTag = "sensor_id=";
    String valueTag = "&value="; 
    String httpRequestData = sensorTag+sensor_id+valueTag+literByMin;
    Serial.println(httpRequestData);
    http.POST(httpRequestData);
    http.end();
  }
}

void updateFromServer(){
  if (WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin("http://192.168.1.25:8000/post/api?sensor_id=1");
    http.GET();
    JSONVar updatedJsonValue = JSON.parse(http.getString());
    Serial.println(updatedJsonValue);
    http.end();
    int updatedMinimumValue = (int)updatedJsonValue["minimum_value"];
    int updatedAlertValue = (int)updatedJsonValue["alert_value"];
    
    mini = updatedMinimumValue;
    alert = updatedAlertValue;
    
    
  }
}
void displayToLcd(int data1,int data2,int data3){
    display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(SSD1306_WHITE); // Draw white text
      display.cp437(true);         // Use full 256 char 'Code Page 437' font
      display.setCursor(0,0);
      display.print(data1);
      display.print("l/min");
      display.setCursor(0,16);
      display.print("Min:");
      display.print(data2);
      display.setCursor(64,16);
      display.print("Alert:");
      display.print(data3);
      display.display();
}
