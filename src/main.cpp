#include "../include/HackQuarium.h"

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";

void setup() {
	Serial.begin(115200);
	ledInit();
	Serial.print("Hello World");
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");

	//BMEInit();
}

void loop() {
	t_all_data allData;

	parseData(&allData);

	// setAllLeds(0, 0, 1, 0);
	// meteorRain(0, 0, 100, 255, 10, 64, true, 30);
	//thunderstorm(0, 0, 1, 0, 0, 0, 0, 255, 30, random(5000));
	// simpleChase(0, 0, 0, 255, 20);
	// getCurrentWeather();
	// delay(3000);
	//printAirSensorValue();
    // delay(1000);
}