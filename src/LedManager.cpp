#include "../include/HackQuarium.h"

// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

CRGBW leds[LED_COUNT];
CRGB *ledsRGB = (CRGB *) &leds[0];
 
const uint8_t brightness = 128;


void	ledInit() {
	FastLED.addLeds<WS2812B, LED_PIN, RGB>(ledsRGB, getRGBWsize(LED_COUNT));
	FastLED.setBrightness(brightness);
	FastLED.show();
}



void	setAllLeds(int r, int g, int b, int w) {
	int i;
	for (i = 0; i < LED_COUNT; i++) {
		setPixel(i, r, g, b, w);
	}
	// Serial.println("   setAllLeds()");
}

void	setPixel(int i, int r, int g, int b, int w) {
	float	brightness = getBrightness();
	leds[i] = CRGBW(r*brightness, g*brightness, b*brightness, w*brightness);
}

void	stripShow() {
	FastLED.show();
	// Serial.println("FastLED.show() called");
}



void thunderstorm(byte red1, byte green1, byte blue1, byte white1, int SparkleDelay, int SpeedDelay) {
	int		Pixel = random(LED_COUNT);
	int		count;
	int		repeatThunder = random(4);
	CRGBW	currentColor = calculColors();

	if (repeatThunder == 0)
		repeatThunder = 1;
	for(count = 0; count <= repeatThunder; count++) {
		Serial.println("------ Thunder ------");
		setAllLeds(currentColor.r, currentColor.g, currentColor.b, currentColor.w);
		for(count = 0; count < random(15, 50); count++) {
			if (Pixel + count >= LED_COUNT - 1) {
				break;
			}
			setPixel(Pixel + count, red1, green1, blue1, white1);
		}
		vTaskDelay(SparkleDelay);
		for(count = 0; count < random(50); count++) {
			if (Pixel + count >= LED_COUNT - 1) {
				break;
			}
			leds[Pixel + count] = CRGBW(currentColor.r, currentColor.g, currentColor.b, currentColor.w);
		}
		vTaskDelay(random(150));
	}
	setAllLeds(currentColor.r, currentColor.g, currentColor.b, currentColor.w);
	if (random(2) == 1) {
		thunderstorm(red1, green1, blue1, white1, SparkleDelay, SpeedDelay);
	}
	else {
		vTaskDelay(SpeedDelay);
	}
}

void	colorTransitionAllLed(byte red, byte green, byte blue, byte white, int speed) {
	int n = 255;
	int	index = 0;
	int	Rnew;
	int	Gnew;
	int	Bnew;
	int	Wnew;
	// Serial.println("in colorTransitionAllLed()");
	CRGBW startColor[LED_COUNT];
	for (int tempI = 0; tempI < LED_COUNT; tempI++) {
		startColor[tempI] = leds[tempI];
	}

	for (int i = 0; i <= n; i++)
	{
		for (index = 0; index < LED_COUNT; index++) {
			Rnew = (red - startColor[index].r) * i / n + startColor[index].r;
			Gnew = (green - startColor[index].g) * i / n + startColor[index].g;
			Bnew = (blue - startColor[index].b) * i / n + startColor[index].b;
			Wnew = (white - startColor[index].w) * i / n + startColor[index].w;
			setPixel(index, Rnew, Gnew, Bnew, Wnew);
		}
		vTaskDelay(speed/n);
	}
	// Serial.println("end colorTransitionAllLed()");
}

void	colorTransitionAllStrip(byte red1, byte green1, byte blue1, byte white1, int speed, int indexLed) {
	int n = 50;
	int	strip = 0;
	int	Rnew;
	int	Gnew;
	int	Bnew;
	int	Wnew;
	CRGBW startColor[LED_COUNT];
	for (int tempI = 0; tempI < LED_COUNT; tempI++) {
		startColor[tempI] = leds[tempI];
	}

	for (int i = 0; i <= n; i++)
	{
		strip = 0;
		while (strip < 6) {
			if (strip % 2 == 0) {
				setPixel(indexLed + (LED_COUNT/6) * strip, Rnew, Gnew, Bnew, Wnew);
				Rnew = (red1 - startColor[indexLed + (LED_COUNT/6)].r) * i / n + startColor[indexLed + (LED_COUNT/6)].r;
				Gnew = (green1 - startColor[indexLed + (LED_COUNT/6)].g) * i / n + startColor[indexLed + (LED_COUNT/6)].g;
				Bnew = (blue1 - startColor[indexLed + (LED_COUNT/6)].b) * i / n + startColor[indexLed + (LED_COUNT/6)].b;
				Wnew = (white1 - startColor[indexLed + (LED_COUNT/6)].w) * i / n + startColor[indexLed + (LED_COUNT/6)].w;
			}
			else {
				Rnew = (red1 - startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].r) * i / n + startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].r;
				Gnew = (green1 - startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].g) * i / n + startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].g;
				Bnew = (blue1 - startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].b) * i / n + startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].b;
				Wnew = (white1 - startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].w) * i / n + startColor[(LED_COUNT/6) * (strip + 1) - indexLed - 1].w;
				setPixel((LED_COUNT/6) * (strip + 1) - indexLed - 1, Rnew, Gnew, Bnew, Wnew);

			}
			strip++;
		}
		vTaskDelay(speed/n);
	}
}

/*
** colorTransitionOneStrip :
** NOT FINISH
*/
void	colorTransitionOneStrip(byte red1, byte green1, byte blue1, byte white1, int speed, int indexStrip) {
	int n = 50;
	// int	index = (LED_COUNT / 6) * indexStrip;
	int	indexEnd = (LED_COUNT / 6) * (indexStrip + 1) - 1;
	int	Rnew;
	int	Gnew;
	int	Bnew;
	int	Wnew;
	CRGBW startColor = leds[(LED_COUNT / 6) * indexStrip];
	// for (int tempI = 0; tempI < LED_COUNT; tempI++) {
	// 	startColor[tempI] = leds[tempI];
	// }

	for (int i = 0; i <= n; i++)
	{
		for (int index = (LED_COUNT / 6) * indexStrip; index <= indexEnd; index++) {
			Rnew = (red1 - startColor.r) * i / n + startColor.r;
			Gnew = (green1 - startColor.g) * i / n + startColor.g;
			Bnew = (blue1 - startColor.b) * i / n + startColor.b;
			Wnew = (white1 - startColor.w) * i / n + startColor.w;
			setPixel(index, Rnew, Gnew, Bnew, Wnew);
		}
		vTaskDelay(speed/n);
	}
}

void	sunSimulation(byte red1, byte green1, byte blue1, byte white1, int speed) {
	int countLed = 0;

	HACKQUARIUM.inSunSimulation = 1;
	// setAllLeds(red0, green0, blue0, white0);
	Serial.println("\nin sunSimulation()");
	while(countLed < LED_COUNT/6) {
		colorTransitionAllStrip(red1, green1, blue1, white1, speed/(LED_COUNT/6), countLed);
		countLed++;
	}
	Serial.println("out sunSimulation()");
	HACKQUARIUM.inSunSimulation = 0;
}


void	cloudEffect(int speed) {
	CRGBW actualColors = calculColors();
	HACKQUARIUM.inCloudSimulation = 1;
	colorTransitionAllLed(actualColors.r, actualColors.g, actualColors.b, actualColors.w, 5000);
	int countLine = 0;

	for(countLine = 0; countLine < 6; countLine++) {
		// Serial.print("           in cloudEffect() 1\n");
		colorTransitionOneStrip(actualColors.red / 4,
								actualColors.green / 4,
								actualColors.blue / 4,
								actualColors.white / 4,
								(speed / 2) / 6,
								countLine);
	}
	actualColors = calculColors();
	for(countLine = 0; countLine < 6; countLine++) {
		// Serial.print("           in cloudEffect() 2\n");
		colorTransitionOneStrip(actualColors.red,
								actualColors.green,
								actualColors.blue,
								actualColors.white,
								(speed / 2) / 6,
								countLine);
	}
	HACKQUARIUM.inCloudSimulation = 0;
}