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