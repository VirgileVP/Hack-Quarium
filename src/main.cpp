#include "../include/HackQuarium.h"

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";

t_all_data AllStaticData::allData;

static TaskHandle_t userTaskHandle = 0;
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t LightTaskHandle = 0;
static TaskHandle_t WeatherTaskHandle = 0;
static TaskHandle_t SensorTaskHandle = 0;

void FastLEDshowESP32() {
	if (userTaskHandle == 0)
	{
		userTaskHandle = xTaskGetCurrentTaskHandle();
		xTaskNotifyGive(FastLEDshowTaskHandle);
	}
}

void FastLEDshowTask(void *pvParameters) {
    while(true)
    {
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        stripShow();
        userTaskHandle = 0; //so we can't have two display tasks at the same time
    }
}

void LightTask(void *pvParameters) {
	while (true) {
		//thunderstorm(0, 0, 10, 5, 0, 0, 0, 255, 50, random(5000));
		//simpleChase(AllStaticData::allData, 255, 0, 0, 255, 12);
		//simpleChase(AllStaticData::allData, 0, 0, 255, 0, 100);
	}
}

void WeatherTask(void *pvParameters) {
	while (true) {
		weatherManager(AllStaticData::allData);
		delay(1800000);
	}
}

void SensorTask(void *pcParameters) {
	while (true)
	{

	}
}

void setup() {
	Serial.begin(115200);
	ledInit();

	//pinMode(WATERFALL_PIN, OUTPUT);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");

	//BMEInit();

	

	Serial.println("Setup()");

	xTaskCreatePinnedToCore(
					FastLEDshowTask,
					"FastLEDshowTask",
					1000,
					NULL,
					1,
					&FastLEDshowTaskHandle,
					0);
	xTaskCreatePinnedToCore(
					LightTask,
					"LightTask",
					10000,
					NULL,
					1,
					&LightTaskHandle,
					1);
	xTaskCreatePinnedToCore(
					WeatherTask,
					"WeatherTask",
					10000,
					NULL,
					1,
					&WeatherTaskHandle,
					1);
	xTaskCreatePinnedToCore(
					SensorTask,
					"SensorTask",
					10000,
					NULL,
					1,
					&SensorTaskHandle,
					1);

}

void loop() {
	FastLEDshowESP32();
}