#include "../include/HackQuarium.h"

HTTPClient http;

const String APIURI = "http://api.openweathermap.org/data/2.5/weather?q=Manaus,3663517pt&APPID=9d108f420d9e997ca7cafa26e3a8488c&units=metric";

void	getAPICurrentWeather(){
	// DynamicJsonDocument doc(806);
	StaticJsonDocument<1024> doctest;
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

	deserializeJson(doctest, payload);


	WEATHER.gpsCoord.latitude = doctest["coord"]["lat"];
	WEATHER.gpsCoord.longitude = doctest["coord"]["lon"];

	WEATHER.skyStatement.clouds = doctest["clouds"]["all"];

	WEATHER.timeInfo.timeZone = doctest["timezone"];
	WEATHER.timeInfo.sunrise = doctest["sys"]["sunrise"];
	WEATHER.timeInfo.sunrise += WEATHER.timeInfo.timeZone;
	WEATHER.timeInfo.sunset = doctest["sys"]["sunset"];
	WEATHER.timeInfo.sunset += WEATHER.timeInfo.timeZone;
	

	WEATHER.airInfo.averageTemp = doctest["main"]["temp"];
	WEATHER.airInfo.minTemp = doctest["main"]["temp_min"];
	WEATHER.airInfo.maxTemp = doctest["main"]["temp_max"];
	WEATHER.airInfo.pressure = doctest["main"]["pressure"];
	WEATHER.airInfo.humidity = doctest["main"]["humidity"];

	WEATHER.mainWeather = doctest["weather"][0]["id"];

	if (AllStaticData::allData.secondFromEpoch == 0) {
		AllStaticData::allData.secondFromEpoch = doctest["dt"];
		AllStaticData::allData.secondFromEpoch += WEATHER.timeInfo.timeZone;
	}

	// WEATHER.timeInfo.sunrise = AllStaticData::allData.secondFromEpoch + 15;

}