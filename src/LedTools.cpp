#include "../include/HackQuarium.h"

float   getBrightness() {
	int		brightnessPercent = map(WEATHER.skyStatement.clouds, 0, 100, 100, 50);
	float	retBrgightness = float(brightnessPercent) / 100;
	return (retBrgightness);
}

CRGBW	calculNightColors() {
	CRGBW	retColor;
	float	cloudColorCalibration = 1;

	Serial.println("NIGHT");
	if (AllStaticData::allData.secondFromEpoch % 60 >= (WEATHER.timeInfo.sunset % 60 + 5) ||
		AllStaticData::allData.secondFromEpoch % 60 <= 2) {
		Serial.println("  FULL NIGHT");
		// FULL NIGHT

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    < 50% cloudness");
			// < 50% cloudness

			retColor.r = 0;
			retColor.g = 0;
			retColor.b = 7;
			retColor.w = 15;
		}
		else {
			Serial.println("    > 50% cloudness");
			// > 50% cloudness

			cloudColorCalibration = float(map(WEATHER.skyStatement.clouds, 0, 100, 20, 100));
			cloudColorCalibration = cloudColorCalibration / 100;
			retColor.r = 0 * cloudColorCalibration;
			retColor.g = 0 * cloudColorCalibration;
			retColor.b = 10 * (1 - cloudColorCalibration);
			retColor.w = 7;
			}
	}
	else {
		// SOFT NIGHT

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    < 50% cloudness");
			// < 50% cloudness

			retColor.r = 50;
			retColor.g = 15;
			retColor.b = 0;
			retColor.w = 0;
		}
		else {
			Serial.println("    > 50% cloudness");
			// > 50% cloudness

			cloudColorCalibration = float(map(WEATHER.skyStatement.clouds, 0, 100, 20, 100));
			cloudColorCalibration = cloudColorCalibration / 100;
			retColor.r = 7 * cloudColorCalibration;
			retColor.g = 7 * cloudColorCalibration;
			retColor.b = 0 * (1 - cloudColorCalibration);
			retColor.w = 25;
			}
			
	}
	return (retColor);
}

CRGBW	calculDayColors() {
	CRGBW	retColor;
	float	cloudColorCalibration = 1;
	Serial.println("DAY");
	if (AllStaticData::allData.secondFromEpoch % 60 >= WEATHER.timeInfo.sunrise % 60 + 4 &&
		AllStaticData::allData.secondFromEpoch % 60 <= WEATHER.timeInfo.sunset % 60 - 2) {
		// FULL DAY

		Serial.println("  FULL DAY");
		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    < 50% cloudness");
			// < 50% cloudness

			retColor.r = 255;
			retColor.g = 100;
			retColor.b = 0;
			retColor.w = 255;
		}
		else {
			Serial.println("    > 50% cloudness");
			// > 50% cloudness

			cloudColorCalibration = float(map(WEATHER.skyStatement.clouds, 0, 100, 20, 100));
			cloudColorCalibration = cloudColorCalibration / 100;

			retColor.r = 100 * cloudColorCalibration;
			retColor.g = 40 * cloudColorCalibration;
			retColor.b = 100 * (1 - cloudColorCalibration);
			retColor.w = 200;
			}
	}
	else {
		// SOFT DAY

		Serial.println("  SOFT DAY");
		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    < 50% cloudness");
			// < 50% cloudness
			retColor.r = 255;
			retColor.g = 100;
			retColor.b = 0;
			retColor.w = 100;
		}
		else {
			Serial.println("    > 50% cloudness");
			// > 50% cloudness

			cloudColorCalibration = float(map(WEATHER.skyStatement.clouds, 0, 100, 20, 100));
			cloudColorCalibration = cloudColorCalibration / 100;
				
			retColor.r = 100 * cloudColorCalibration;
			retColor.g = 40 * cloudColorCalibration;
			retColor.b = 100 * (1 - cloudColorCalibration);
			retColor.w = 180;
		}
	}
	return (retColor);
}

CRGBW	calculColors() {
	CRGBW	retColor;
	if (AllStaticData::allData.secondFromEpoch < WEATHER.timeInfo.sunrise) {
		// NIGHT
		retColor = calculNightColors();
	}
	else {
		// DAY
		retColor = calculDayColors();
	}
	return (retColor);
}