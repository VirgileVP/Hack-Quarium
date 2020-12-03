#ifndef HACK_QUARIUM_H
# define HACK_QUARIUM_H
# define FASTLED_ESP32_I2S
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "FastLED_RGBW.h"
# include <SPI.h>
# include <Wire.h>
# include <ArduinoJson.h>
# include <Adafruit_Sensor.h>
# include <Adafruit_BME280.h>
# include <Adafruit_NeoPixel.h>
# include <WiFi.h>
# include <HTTPClient.h>

# include <time.h>
# include <ctime>
# include <iostream>


# define LED_PIN 22
# define LED_COUNT 108

# define MOISTURE_SENSOR_PIN 15
# define AIR_SENSOR_PIN 13

# define WATERFALL_PIN 12
# define RAIN_PIN 32

# define WEATHER AllStaticData::allData.currentWeather
# define HACKQUARIUM AllStaticData::allData.hackQuariumData

// #define SEALEVELPRESSURE_HPA (1013.25)

// Adafruit_BME280 bme;

struct colorRgbw {
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	white;
};

typedef struct			s_strip_led
{
	int				index;
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	white;
}						t_strip_led;

typedef	struct			s_gps_coord
{
	float	longitude;
	float	latitude;
}						t_gps_coord;

/*
** averageTemp: average API temperature (°celsius)
** minTemp:     min API temperature (°celsius)
** maxTemp:     max API temperature (°celsius)
** pressure:    API pressure (hPa)
** humidity:    API humidity(percent)
*/
typedef	struct			s_API_air_info
{
	float	averageTemp;
	float	minTemp;
	float	maxTemp;
	int		pressure;
	int		humidity;
}						t_API_air_info;

/*
** sunrise, sunset: in second
** timeZone:        shift in seconds from UTC
*/
typedef	struct			s_time_info
{
	int		sunrise;
	int		sunset;
	int		timeZone;
}						t_time_info;

/*
** clouds: API clouds (percent)
*/
typedef	struct			s_API_sky
{
	int		clouds;
}						t_API_sky;

typedef	struct			s_API_current_weather
{
	int				mainWeather;
	t_gps_coord		gpsCoord;
	t_API_sky		skyStatement;
	t_time_info		timeInfo;
	s_API_air_info	airInfo;
}						t_API_current_weather;

/*
** temperature: °celcius
** humidity:    percent
** pressure:    hPa
** altitude:    meters from see level
*/
typedef	struct			s_air_sensor
{
	float	temperature;
	int		humidity;
	int		pressure;
	float	altitude;
}						t_air_sensor;

// typedef	struct			s_ground_sensor
// {
// 	int		moisture;
// }						t_ground_sensor;

typedef struct			s_HackQuarium_data
{
	t_strip_led		stripLed[LED_COUNT];
	t_air_sensor	airSensor;
	// t_ground_sensor	groundSensor;
}						t_HackQuarium_data;

typedef struct			s_all_data
{
	t_API_current_weather	currentWeather;
	t_HackQuarium_data		hackQuariumData;
	int						secondFromEpoch;
	int						activeSunSimulation;
}						t_all_data;

class AllStaticData {
	public:
		static t_all_data allData;
};



void	test();

void	ledInit();
void	stripShow();
void	stripGlobalShow();
void	setPixel(int i, int r, int g, int b, int w);
void	setAllLeds(int r, int g, int b, int w);
void	colorTransitionAllLed(byte red, byte green, byte blue, byte white, int speed);
void	sunSimulation(byte red1, byte green1, byte blue1, byte white1, int speed);
void	thunderstorm(byte red1, byte green1, byte blue1, byte white1, int SparkleDelay, int SpeedDelay);

float	getBrightness();
CRGBW	calculColors();

void	BMEInit();
void	printAirSensorValue();

void	weatherManager();
void	getAPICurrentWeather();



#endif