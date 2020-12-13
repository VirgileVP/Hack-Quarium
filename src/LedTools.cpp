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
	if (AllStaticData::allData.secondFromEpoch/3600 % 24 >= (WEATHER.timeInfo.sunset/3600 % 24 + 5) ||
		AllStaticData::allData.secondFromEpoch/3600 % 24 <= 2) {
		Serial.println("  FULL NIGHT : " + String(getActualHour()) + "H" + String(getActualMinutes()));
		// FULL NIGHT

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
			// < 50% cloudness

			retColor.r = 0;
			retColor.g = 0;
			retColor.b = 7;
			retColor.w = 15;
		}
		else {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
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
		Serial.println("  SOFT NIGHT : " + String(getActualHour()) + "H" + String(getActualMinutes()));
		// SOFT NIGHT

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
			// < 50% cloudness

			retColor.r = 40;
			retColor.g = 10;
			retColor.b = 0;
			retColor.w = 0;
		}
		else {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
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
	if (AllStaticData::allData.secondFromEpoch/3600 % 24 > WEATHER.timeInfo.sunrise/3600 % 24 + 4 &&
		AllStaticData::allData.secondFromEpoch/3600 % 24 <= WEATHER.timeInfo.sunset/3600 % 24 - 2) {
		Serial.println("  FULL DAY : " + String(getActualHour()) + "H" + String(getActualMinutes()));
		// FULL DAY

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
			// < 50% cloudness

			retColor.r = 255;
			retColor.g = 100;
			retColor.b = 0;
			retColor.w = 255;
		}
		else {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
			// > 50% cloudness

			cloudColorCalibration = float(map(WEATHER.skyStatement.clouds, 0, 100, 20, 100));
			cloudColorCalibration = cloudColorCalibration / 100;

			retColor.r = 100 * cloudColorCalibration;
			retColor.g = 40 * cloudColorCalibration;
			retColor.b = 60 * (1 - cloudColorCalibration);
			retColor.w = 200;
			}
	}
	else {
		Serial.println("  SOFT DAY : " + String(getActualHour()) + "H" + String(getActualMinutes()));
		// SOFT DAY

		if (WEATHER.skyStatement.clouds <= 50) {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
			// < 50% cloudness
			retColor.r = 255;
			retColor.g = 100;
			retColor.b = 0;
			retColor.w = 100;
		}
		else {
			Serial.println("    " + String(WEATHER.skyStatement.clouds) + "% cloudness");
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

	if (AllStaticData::allData.secondFromEpoch/3600 % 24 >= WEATHER.timeInfo.sunset/3600 % 24 && AllStaticData::allData.secondFromEpoch/3600 % 24 <= 23 
	 || AllStaticData::allData.secondFromEpoch/3600 % 24 < WEATHER.timeInfo.sunset/3600 % 24 && AllStaticData::allData.secondFromEpoch < WEATHER.timeInfo.sunrise/3600 % 24) {
		// NIGHT
		retColor = calculNightColors();
	}
	else {
		// DAY
		retColor = calculDayColors();
	}
	return (retColor);
}