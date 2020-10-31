#include <WiFi.h>
#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";

// OpenWeatherMap consts
const String endpoint = "http://api.openweathermap.org/data/2.5/weather?q=3663517,pt&APPID=";
const String key = "9d108f420d9e997ca7cafa26e3a8488c";


HTTPClient http;

#define LED_PIN 23
#define LED_COUNT 108

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_RGBW + NEO_KHZ800);



void setup() {
  Serial.begin(115200);
  strip.begin();
  strip.show();
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
 
  Serial.println("Connected to the WiFi network");
}

void loop() {
  onAllLed(0, 0, 0, 255);
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status

    
    HTTPClient http;
 
    http.begin(endpoint + key); //Specify the URL
    int httpCode = http.GET();  //Make the request
 
    if (httpCode > 0) { //Check for the returning code
 
        String payload = http.getString();
        Serial.println(httpCode);
        Serial.println(payload);
      }
 
    else {
      Serial.println("Error on HTTP request");
    }
 
    http.end(); //Free the resources
  }
  delay(3000);
}

void onAllLed(int r, int g, int b, int w) {
  int i = 0;
  for (i; i < LED_COUNT; i++) {
    strip.setPixelColor(i, r, g, b, w);
  }
  strip.show();
}
