#include "../include/HackQuarium.h"

// WIFI consts
const char* ssid = "octopus-exofam";
const char* password = "0123456789";

t_all_data AllStaticData::allData;

Adafruit_BME280 bme;

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
	// nextColor = calculColors();
	// Serial.println(nextColor.r);
	// Serial.println(nextColor.g);
	// Serial.println(nextColor.b);
	// Serial.println(nextColor.w);
	// colorTransitionAllLed(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 10000);
	// colorTransitionAllLed(0, 0, 7, 15, 10000);
	colorTransitionAllLed(255, 0, 0, 0, 1000);
	colorTransitionAllLed(0, 255, 0, 0, 1000);
	colorTransitionAllLed(0, 0, 255, 0, 1000);
	colorTransitionAllLed(0, 0, 0, 255, 1000);
	colorTransitionAllLed(255, 255, 255, 255, 1000);
	colorTransitionAllLed(0, 0, 0, 0, 1000);
	delay(1000);
	while (true) {
		Serial.println("in LightTask()");
		if (HACKQUARIUM.inSunSimulation == 0) {
			nextColor = calculColors();
			colorTransitionAllLed(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 10000);
			delay(900010); // 15 minutes et 10 centiemes
		}
		while (WEATHER.mainWeather >= 200 && WEATHER.mainWeather <= 232 && HACKQUARIUM.inSunSimulation == 0) {
			thunderstorm(0, 0, 0, 255, 10, random(5000));
		}
	}
}

void RainTask(void *pvParameters) {
	while (true) {
		// Serial.println("in RainTask()");
		while (softRain() == 1) {
			while (checkHumidity() == 0) {
				delay(10000);
			}
			digitalWrite(WATERFALL_PIN, HIGH); //OFF
			vTaskDelay(30000);
			digitalWrite(WATERFALL_PIN, LOW); //ON
			vTaskDelay(10000);
		}
		while (normalRain() == 1) {
			digitalWrite(WATERFALL_PIN, HIGH); //OFF
			vTaskDelay(20000);
			digitalWrite(WATERFALL_PIN, LOW); //ON
			vTaskDelay(20000);
		}
		while (heavyRain() == 1) {
			digitalWrite(WATERFALL_PIN, HIGH); //OFF
			vTaskDelay(10000);
			digitalWrite(WATERFALL_PIN, LOW); //ON
			vTaskDelay(30000);

		}
		delay(5000);
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
		// int temperature = bme.readTemperature();
		// int humidity = bme.readHumidity();
		// int pressure = bme.readPressure() / 100.0F;
		// Serial.println(temperature);
		// Serial.println(humidity);
		// Serial.println(pressure);
		// vTaskDelay(1000);
		// HACKQUARIUM.airSensor.humidity = bme.readHumidity();
		// HACKQUARIUM.airSensor.pressure = bme.readPressure();
		// HACKQUARIUM.airSensor.temperature = bme.readTemperature();
		delay(1000);
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
		Serial.println("In SunTask()");
		nextColor = calculColors();
		// Serial.print("    ");
		// Serial.print("    actual : ");
		// Serial.println(AllStaticData::allData.secondFromEpoch);
		// Serial.print("   sunrise : ");
		// Serial.println(WEATHER.timeInfo.sunrise - AllStaticData::allData.secondFromEpoch);
		// Serial.print("    sunset : ");
		// Serial.println(WEATHER.timeInfo.sunset - AllStaticData::allData.secondFromEpoch);
		if (AllStaticData::allData.secondFromEpoch != 0 && AllStaticData::allData.secondFromEpoch == WEATHER.timeInfo.sunrise) {
			Serial.println("SUNRISE");
			sunSimulation(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 2100000);
		}
		else if (AllStaticData::allData.secondFromEpoch != 0 && AllStaticData::allData.secondFromEpoch == WEATHER.timeInfo.sunset) {
			Serial.println("SUNSET");
			sunSimulation(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 2100000);
			nextColor = calculColors();
			sunSimulation(nextColor.r, nextColor.g, nextColor.b, nextColor.w, 2100000);
			// sunSimulation(50, 12, 0, 0, 1800000);
			// colorTransitionAllLed(0, 0, 7, 7, 180000);
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
	// BMEInit();
	// bme.begin(0x76);  
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
	xTaskCreatePinnedToCore(
					RainTask,
					"RainTask",
					10000,
					NULL,
					1,
					&RainTaskHandle,
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