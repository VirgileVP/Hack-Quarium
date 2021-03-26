#include "../include/HackQuarium.h"

void weatherManager() {
	getAPICurrentWeather();

	Serial.print("actual : ");
	Serial.println(AllStaticData::allData.secondFromEpoch);
	Serial.print("sunrise : ");
	Serial.println(WEATHER.timeInfo.sunrise);
	Serial.print("sunset : ");
	Serial.println(WEATHER.timeInfo.sunset);
}

int		isThunder() {
	if (WEATHER.mainWeather == 212 || WEATHER.mainWeather == 221) { // Heavy Thunderstorm
		return (2);
	}
	else if (WEATHER.mainWeather >= 200 && WEATHER.mainWeather <= 232) { // thunderstorm
		return (1);
	}
	return (0);
}