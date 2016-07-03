

#include "DHT.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

#define DHTPIN D4 
#define DHTTYPE DHT11
/* Set these to your desired credentials. */
const char *ssid = "test";
const char *password = "password";
//const char *ssid = "VM149595-2G";
//const char *password = "vvzqnkxg";
float h,t;
ESP8266WebServer server(80);

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
 * connected to this access point to see it.
 */
void handleRoot() {
	server.send(200, "application/json", "{\"h\": "+String(h)+", \"t\": "+String(t)+"}");
}

DHT dht(DHTPIN, DHTTYPE);
void setup() {
  pinMode(D3,OUTPUT);
  digitalWrite(D3,HIGH);
   dht.begin();
	delay(1000);
	Serial.begin(115200);
	Serial.println();
	Serial.print("Configuring access point...");	
	WiFi.softAP(ssid);

IPAddress myIP = WiFi.softAPIP();
//  WiFi.begin(ssid, password);
//  
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
	Serial.print("AP IP address: ");
	Serial.println(myIP);
//Serial.println(WiFi.localIP());
	server.on("/", handleRoot);
	server.begin();
	Serial.println("HTTP server started");
}

int m = millis();

void loop() {
  if(millis()>m+2000){
  m=millis();
  h = dht.readHumidity();  
  t = dht.readTemperature();
    if (isnan(h) || isnan(t) ) {
      Serial.println("Failed to read from DHT sensor!");      
    }else{
      Serial.println("H" + String(h) + "T" + String(t));
    }
  }
  
	server.handleClient();
}