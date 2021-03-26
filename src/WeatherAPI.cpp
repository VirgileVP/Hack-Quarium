#include "../include/HackQuarium.h"

HTTPClient http;

const String APIURI = "http://api.openweathermap.org/data/2.5/weather?q=Manaus,3663517pt&APPID=9d108f420d9e997ca7cafa26e3a8488c&units=metric";

void	getAPICurrentWeather(){
	// DynamicJsonDocument doc(806);
	StaticJsonDocument<1024> jsonWeather;
	String payload;
	if ((WiFi.status() == WL_CONNECTED)) {
		HTTPClient http;

		http.begin(APIURI);
		int httpCode = http.GET();

		if (httpCode > 0) {
				payload = http.getString();
			}
		else {
			Serial.println("Error on HTTP request");
		}
		http.end();
	}

	deserializeJson(jsonWeather, payload);


	WEATHER.gpsCoord.latitude = jsonWeather["coord"]["lat"];
	WEATHER.gpsCoord.longitude = jsonWeather["coord"]["lon"];

	WEATHER.skyStatement.clouds = jsonWeather["clouds"]["all"];

	WEATHER.timeInfo.timeZone = jsonWeather["timezone"];
	WEATHER.timeInfo.sunrise = jsonWeather["sys"]["sunrise"];
	WEATHER.timeInfo.sunrise += WEATHER.timeInfo.timeZone;
	WEATHER.timeInfo.sunset = jsonWeather["sys"]["sunset"];
	WEATHER.timeInfo.sunset += WEATHER.timeInfo.timeZone;
	

	WEATHER.airInfo.averageTemp = jsonWeather["main"]["temp"];
	WEATHER.airInfo.minTemp = jsonWeather["main"]["temp_min"];
	WEATHER.airInfo.maxTemp = jsonWeather["main"]["temp_max"];
	WEATHER.airInfo.pressure = jsonWeather["main"]["pressure"];
	WEATHER.airInfo.humidity = jsonWeather["main"]["humidity"];

	WEATHER.mainWeather = jsonWeather["weather"][0]["id"];

	if (AllStaticData::allData.secondFromEpoch == 0) {
		AllStaticData::allData.secondFromEpoch = jsonWeather["dt"];
		// AllStaticData::allData.secondFromEpoch += WEATHER.timeInfo.timeZone;
		AllStaticData::allData.secondFromEpoch += 3600;
	}

	// WEATHER.timeInfo.sunrise = AllStaticData::allData.secondFromEpoch + 15;

}