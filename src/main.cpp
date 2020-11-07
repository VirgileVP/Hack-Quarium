#include "../include/HackQuarium.h"

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";




class LedShowTask : public Task {
public:
    void loop() {
        Serial.println("Led task");
        delay(500);
    }
} ledShowTask;


class WeatherTask : public Task {
public:
    void loop() {
        Serial.println("Weather task");
        delay(2000);
    }
} weatherTask;





void setup() {
	Serial.begin(115200);
	ledInit();

	pinMode(WATERFALL_PIN, OUTPUT);
	/*Serial.print("Hello World");
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");
*/
	//BMEInit();


	Scheduler.start(&ledShowTask);
	Scheduler.start(&weatherTask);
	Serial.println(F("SETUP"));
	Scheduler.begin();
}

void loop() {
	// t_all_data allData;

	// parseData(&allData);
	// thunderstorm(0, 0, 1, 0, 0, 0, 0, 255, 7, random(5000));
	// meteorRain(0, 0, 100, 255, 10, 64, true, 30);
	// simpleChase(0, 0, 0, 255, 20);
	// getCurrentWeather();
	// delay(3000);
	//printAirSensorValue();
    // delay(1000);
}