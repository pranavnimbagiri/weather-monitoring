#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHTPIN 19
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#define WLAN_SSID "Airtel_Zerotouch_5G"
#define WLAN_PASS "Pranav1974@"
Adafruit_BMP085 bmp;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.print("connecting to");
  Serial.println(WLAN_SSID);
  WiFi.begin(WLAN_SSID,WLAN_PASS);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.print(".");
    }
    Serial.println("wifi connected");
    Serial.println("IP Address");
    Serial.println(WiFi.localIP());
    if(!bmp.begin()){
      Serial.println("could not find a valid bmp085/bmp180 sensor");
      while(1){}
      }

      dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status()==WL_CONNECTED){
    WiFiClient client;
    Serial.print("temperature=");
    Serial.print(bmp.readTemperature());
    Serial.println("C");

    Serial.print("pressure=");
    Serial.print(bmp.readPressure());
    Serial.println("PA");
    Serial.println("altitude=");
    Serial.print(bmp.readAltitude());
    Serial.print("meters");
    float h=dht.readHumidity();
    
    if (isnan(h)){
      Serial.println("failed to read from DHT center");
      return;
      
      }
      else{
        Serial.println("humidity");
        Serial.print(h);
        }
    }

    else{
      Serial.println("WiFiDisconnected");
  
      }
      delay(5000);
}
