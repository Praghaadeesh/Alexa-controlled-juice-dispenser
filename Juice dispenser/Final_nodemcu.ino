
#include<SoftwareSerial.h> //Included SoftwareSerial Library
//Started SoftwareSerial at RX and TX pin of ESP8266/NodeMCU
SoftwareSerial s(3,1);
#ifdef ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <Espalexa.h>
// define the GPIO connected with Relays


// prototypes
boolean connectWifi();

//callback functions
void pump1changed(uint8_t power);
void pump2changed(uint8_t power);
void pump3changed(uint8_t power);
void mixed(uint8_t power);

// WiFi Credentials
const char* ssid = "Praghaadeesh";
const char* password = "9443396650";

// device names
String Device_1_Name = "water";
String Device_2_Name = "juice1";
String Device_3_Name = "juice2";
String Device_4_Name = "mix";

boolean wifiConnected = false;

Espalexa espalexa;

void setup()
{
  Serial.begin(115200);
  s.begin(9600);
  

  // Initialise wifi connection
  wifiConnected = connectWifi();

  if (wifiConnected)
  {
    // Define your devices here.
    espalexa.addDevice(Device_1_Name, pump1changed); //simplest definition, default state off
    espalexa.addDevice(Device_2_Name, pump2changed);
    espalexa.addDevice(Device_3_Name, pump3changed);
    espalexa.addDevice(Device_4_Name, mixed);
    espalexa.begin();
  }
  else
  {
    while (1)
    {
      Serial.println("Cannot connect to WiFi. Please check data and reset the ESP.");
      delay(2500);
    }
  }
}

void loop()
{
  espalexa.loop();
  delay(1);
}

//our callback functions
void pump1changed(uint8_t power)
{
  //Control the device
  if (power == 255)
    {
      s.write(1);
    }
  else if (power == 0)
  {
    ;
  }
}

void pump2changed(uint8_t power)
{
  //Control the device
  if (power == 255)
    {
      s.write(2);
    }
  else if (power == 0)
  {
    ;
  }
}

void pump3changed(uint8_t power)
{
  //Control the device
  if (power == 255)
    {
      s.write(3);
    }
  else if (power == 0)
  {
    ;
  }
}

void mixed(uint8_t power)
{
  //Control the device
  if (power == 255)
    {
      s.write(4);
    }
  else if (power == 0)
  {
    ;
  }
}

// connect to wifi – returns true if successful or false if not
boolean connectWifi()
{
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 20) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
}
