#include "../include/HackQuarium.h"

HTTPClient http;

const String APIURI = "http://api.openweathermap.org/data/2.5/weather?q=Manaus,3663517pt&APPID=9d108f420d9e997ca7cafa26e3a8488c&units=metric";



JsonArray	getCurrentWeather(){
	JsonArray JsonWeather;
	if ((WiFi.status() == WL_CONNECTED)) {
		HTTPClient http;

		http.begin(APIURI);
		int httpCode = http.GET();

		if (httpCode > 0) {
				String payload = http.getString();
				Serial.println(httpCode);
				Serial.println(payload);
			}
		else {
			Serial.println("Error on HTTP request");
		}
		// http.end();
	}
	
	return (JsonWeather); 
}