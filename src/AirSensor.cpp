#include "../include/HackQuarium.h"

// void    BMEInit() {
// 	if (!bme.begin(0x76)) {
// 		Serial.println("Could not find a valid BME280 sensor, check wiring!");
// 		while (1);
// 	}
// }

// void    printAirSensorValue() {
//    	Serial.print("Temperature = ");
// 	Serial.print(bme.readTemperature());
// 	Serial.println("*C");

// 	Serial.print("Pressure = ");
// 	Serial.print(bme.readPressure() / 100.0F);
// 	Serial.println("hPa");

// 	Serial.print("Approx. Altitude = ");
// 	Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
// 	Serial.println("m");

// 	Serial.print("Humidity = ");
// 	Serial.print(bme.readHumidity());
// 	Serial.println("%");

// 	Serial.println();
// }