#include "../include/HackQuarium.h"

int     softRain() {
	if (WEATHER.mainWeather == 200 ||
		WEATHER.mainWeather == 230 ||
		WEATHER.mainWeather >= 300  && WEATHER.mainWeather <= 311 ||
		WEATHER.mainWeather == 500) {
			Serial.println("SoftRain");
			return (1);
	}
	return (0);
}

int     normalRain() {
	if (WEATHER.mainWeather == 201 ||
		WEATHER.mainWeather == 231 ||
		WEATHER.mainWeather >= 312  && WEATHER.mainWeather <= 321 ||
		WEATHER.mainWeather == 501) {
			Serial.println("normalRain");
			return (1);
	}
	return (0);
}

int     heavyRain() {
	if (WEATHER.mainWeather == 202 ||
		WEATHER.mainWeather == 232 ||
		WEATHER.mainWeather >= 502  && WEATHER.mainWeather <= 531) {
			Serial.println("heavyRain");
			return (1);
	}
	return (0);
}

/*
** return 0 if humidity is too high, return 1 else&
*/
int		checkHumidity() {
	if (HACKQUARIUM.airSensor.humidity >= WEATHER.airInfo.humidity)
		return (0);
	return (1);
}

int		checkMoisture() {
	if (HACKQUARIUM.airSensor.humidity >= WEATHER.airInfo.humidity)
		return (0);
	return (1);
}

int		canRain() {
	if (checkHumidity() == 1 && checkMoisture() == 1)
		return (1);
	return (0);
}