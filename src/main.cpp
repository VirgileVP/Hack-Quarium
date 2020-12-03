#include "../include/HackQuarium.h"

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";

t_all_data AllStaticData::allData;

static TaskHandle_t userTaskHandle = 0;
static TaskHandle_t FastLEDshowTaskHandle = 0;
static TaskHandle_t LightTaskHandle = 0;
static TaskHandle_t SunTaskHandle = 0;
static TaskHandle_t RainTaskHandle = 0;
static TaskHandle_t WeatherTaskHandle = 0;
static TaskHandle_t SensorTaskHandle = 0;
static TaskHandle_t TimeTaskHandle = 0;

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
        userTaskHandle = 0;
    }
}

void LightTask(void *pvParameters) {
	CRGBW nextColor;
	// Serial.println(nextColor.r);
	// Serial.println(nextColor.g);
	// Serial.println(nextColor.b);
	// Serial.println(nextColor.w);
	// colorTransitionAllLed(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 6000);
	// colorTransitionAllLed(0, 0, 7, 7, 6000);
	while (true) {
		// Serial.println("in LightTask()");
		// nextColor = calculColors();
		// thunderstorm(0, 0, 0, 255, 20, random(5000));
		// vTaskDelay(900000);

		setAllLeds(5, 5, 25, 25);

		// colorTransitionAllLed(0, 0, 7, 7, 5000);
		// sunSimulation(50, 20, 0, 0, 5000);
		// sunSimulation(50, 20, 0, 30, 5000);
		// colorTransitionAllLed(255, 100, 0, 180, 10000);
		// colorTransitionAllLed(255, 100, 0, 180, 5000);
		// sunSimulation(50, 25, 0, 50, 10000);
		// sunSimulation(50, 12, 0, 0, 5000);
		// colorTransitionAllLed(0, 0, 7, 7, 5000);
		
		// setAllLeds(255, 100, 0, 0);
		// vTaskDelay(5000);
		// setAllLeds(255, 100, 0, 180);
		// vTaskDelay(5000);
		// setAllLeds(0, 0, 100, 255);
		// vTaskDelay(5000);
		// setAllLeds(255, 150, 0, 0);
		// vTaskDelay(5000);
		// setAllLeds(255, 150, 0, 255);
		// vTaskDelay(5000);
		// colorTransitionAllLed(0, 0, 0, 255, 30000);
	}
}

void RainTask(void *pvParameters) {
	while (true) {
		Serial.println("in RainTask()");
		while (WEATHER.mainWeather) {

		}
		digitalWrite(WATERFALL_PIN, HIGH); //OFF
		vTaskDelay(1000);
		digitalWrite(WATERFALL_PIN, LOW); //ON
		vTaskDelay(10000);
	}
}

void WeatherTask(void *pvParameters) {
	while (true) {
		weatherManager();
		Serial.println("Main Weather : ");
		Serial.println(AllStaticData::allData.currentWeather.mainWeather);
		Serial.print("Cloud : ");
		Serial.println(WEATHER.skyStatement.clouds);
		Serial.print("Temperature : ");
		Serial.println(WEATHER.airInfo.averageTemp);
		vTaskDelay(600000);
	}
}

void SensorTask(void *pcParameters) {
	while (true)
	{
		vTaskDelay(10000);
	}
}

void TimeTask(void *pcParameters) {
	while (true) {
		// Serial.println("In TimeTask()");
		if (AllStaticData::allData.secondFromEpoch != 0) {
			AllStaticData::allData.secondFromEpoch++;
			// Serial.print("Sunrise in : ");
			// Serial.println(WEATHER.timeInfo.sunrise - AllStaticData::allData.secondFromEpoch);
			// Serial.print("Sunset in : ");
			// Serial.println(WEATHER.timeInfo.sunset - AllStaticData::allData.secondFromEpoch);
		}
		vTaskDelay(1000);
	}
}

void SunTask(void *pcParameters) {
	CRGBW nextColor;
	while (true) {
		nextColor = calculColors();
		Serial.println("In SunTask()");
		Serial.print("    ");
		Serial.println(AllStaticData::allData.secondFromEpoch);
		Serial.print("    ");
		Serial.println(WEATHER.timeInfo.sunset);
		if (AllStaticData::allData.secondFromEpoch != 0 && AllStaticData::allData.secondFromEpoch == WEATHER.timeInfo.sunrise) {
			Serial.println("SUNRISE");

			sunSimulation(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 360000);
		}
		else if (AllStaticData::allData.secondFromEpoch != 0 && AllStaticData::allData.secondFromEpoch == WEATHER.timeInfo.sunset) {
			Serial.println("SUNSET");
			sunSimulation(50, 12, 0, 0, 1800000);
			colorTransitionAllLed(0, 0, 7, 7, 180000);
			// sunSimulation(0 , 0, 25, 10, 1800000);
		}
		vTaskDelay(1000);
	}
}

void setup() {
	Serial.begin(115200);
	ledInit();

	pinMode(WATERFALL_PIN, OUTPUT);
	pinMode(RAIN_PIN, OUTPUT);
	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");

	//BMEInit();
	setAllLeds(255, 80, 0, 150);

	Serial.println("Setup()");


	bzero(&AllStaticData::allData, sizeof(AllStaticData));
	// setAllLeds(255, 90, 0, 150);
	// FastLED.show();


	xTaskCreatePinnedToCore(
					FastLEDshowTask,
					"FastLEDshowTask",
					1000,
					NULL,
					1,
					&FastLEDshowTaskHandle,
					0);
	xTaskCreatePinnedToCore(
					WeatherTask,
					"WeatherTask",
					10000,
					NULL,
					1,
					&WeatherTaskHandle,
					1);
	xTaskCreatePinnedToCore(
					TimeTask,
					"TimeTask",
					10000,
					NULL,
					1,
					&TimeTaskHandle,
					1);
	xTaskCreatePinnedToCore(
					LightTask,
					"LightTask",
					10000,
					NULL,
					1,
					&LightTaskHandle,
					1);
	xTaskCreatePinnedToCore(
					SunTask,
					"SunTask",
					10000,
					NULL,
					1,
					&SunTaskHandle,
					1);
	// xTaskCreatePinnedToCore(
	// 				RainTask,
	// 				"RainTask",
	// 				10000,
	// 				NULL,
	// 				1,
	// 				&RainTaskHandle,
	// 				1);
	// xTaskCreatePinnedToCore(
	// 				SensorTask,
	// 				"SensorTask",
	// 				10000,
	// 				NULL,
	// 				1,
	// 				&SensorTaskHandle,
	// 				1);
}

void loop() {
	FastLEDshowESP32();
}