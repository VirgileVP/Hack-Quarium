#ifndef HACK_QUARIUM_H
# define HACK_QUARIUM_H
# include <SPI.h>
# include <Wire.h>
# include <ArduinoJson.h>
# include <Adafruit_Sensor.h>
# include <Adafruit_BME280.h>
# include <Adafruit_NeoPixel.h>
# include <Scheduler.h>
# ifdef ESP32
	# include <WiFi.h>
	# include <HTTPClient.h>
# elif defined ESP8266
	# include <ESP8266WiFi.h>
	# include <ESP8266HTTPClient.h>
# endif



# define LED_PIN 3
# define LED_COUNT 108

# define MOISTURE_SENSOR_PIN 15
# define AIR_SENSOR_PIN 13

# define WATERFALL_PIN 12
# define RAIN_PIN 14

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
	int			index;
	colorRgbw	colors;
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
	t_gps_coord	gpsCoord;
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

typedef	struct			s_ground_sensor
{
	int		moisture;
}						t_ground_sensor;

typedef struct			s_HackQuarium_data
{
	t_strip_led		stripLed[LED_COUNT];
	t_air_sensor	airSensor;
	t_ground_sensor	groundSensor;
}						t_HackQuarium_data;


class staticData
{
	public:
		static t_API_current_weather	currentWeather;
		static t_HackQuarium_data		HackQuariumData;
};


void	ledInit();
void	stripShow();
void	stripGlobalShow(t_HackQuarium_data *HackQuariumData);
void	setPixel(int i, int r, int g, int b, int w);
void	setAllLeds(int r, int g, int b, int w);
void	simpleChase(int r, int g, int b, int w, int speedDelay);
void	sunSimulation(byte red0, byte green0, byte blue0, byte white0, byte red1, byte green1, byte blue1, byte white1, int speed);
void	meteorRain(byte red, byte green, byte blue, byte white, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay);
void	thunderstorm(byte red0, byte green0, byte blue0, byte white0, byte red1, byte green1, byte blue1, byte white1, int SparkleDelay, int SpeedDelay);

void    BMEInit();
void	printAirSensorValue();

JsonArray	getCurrentWeather();


#endif