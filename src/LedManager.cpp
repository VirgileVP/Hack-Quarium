#include "../include/HackQuarium.h"

// Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRBW + NEO_KHZ800);

CRGBW leds[LED_COUNT];
CRGB *ledsRGB = (CRGB *) &leds[0];
 
const uint8_t brightness = 128;


void test() {
	int i = 0;
	while (i < LED_COUNT) {
		leds[i] = CRGBW(0, 0, 0, 255);
		i++;
		delay(10);
		FastLED.show();
	}
}

void	ledInit() {
	FastLED.addLeds<WS2812B, LED_PIN, RGB>(ledsRGB, getRGBWsize(LED_COUNT));
	FastLED.setBrightness(brightness);
	FastLED.show();
}

unsigned int saturation(colorRgbw rgbw) {
	float low = min(rgbw.red, min(rgbw.green, rgbw.blue));
	float high = max(rgbw.red, max(rgbw.green, rgbw.blue));
	return round(100 * ((high - low) / high));
}
 
// Returns the value of White
unsigned int getWhite(colorRgbw rgbw) {
	return (255 - saturation(rgbw)) / 255 * (rgbw.red + rgbw.green + rgbw.blue) / 3;
}
 
colorRgbw rgbToRgbw(unsigned int red, unsigned int green, unsigned int blue) {
	unsigned int white = 0;
	colorRgbw rgbw = {red, green, blue, white};
	rgbw.white = getWhite(rgbw);
	return rgbw;
}





void	setAllLeds(int r, int g, int b, int w) {
	int i;
	for (i = 0; i < LED_COUNT; i++) {
		leds[i] = CRGBW(r, g, b, w);
		// strip.setPixelColor(i, r, g, b, w);
	}
	Serial.println("set stripled");
	FastLED.show();
	// stripShow();
}

void	setPixel(int i, int r, int g, int b, int w) {
	leds[i] = CRGBW(r, g, b, w);
	// strip.setPixelColor(i, r, g, b, w);
}





void	stripShow() {
	FastLED.show();
	// Serial.println("FastLED.show() called");
}

void	setLedArray(t_all_data allData, int index, int red, int green, int blue, int white) {
	allData.hackQuariumData.stripLed[index].red = red;
	allData.hackQuariumData.stripLed[index].green = green;
	allData.hackQuariumData.stripLed[index].blue = blue;
	allData.hackQuariumData.stripLed[index].white = white;
	Serial.print("Led Array ");
	Serial.print(index);
	Serial.println(" setted.");
}

void	stripGlobalShow(t_all_data allData) {
	int i = 0;

	while (i < LED_COUNT) {
		setPixel(i, allData.hackQuariumData.stripLed[i].red,
					allData.hackQuariumData.stripLed[i].green,
					allData.hackQuariumData.stripLed[i].blue,
					allData.hackQuariumData.stripLed[i].white);
		Serial.print("setPixel(");
		Serial.print(i);
		Serial.println(")");
		i++;
	}
	stripShow();
	delay(15);
}





void thunderstorm(byte red0, byte green0, byte blue0, byte white0, byte red1, byte green1, byte blue1, byte white1, int SparkleDelay, int SpeedDelay) {
	int Pixel = random(LED_COUNT);
	int count;
	int repeatThunder = random(3);
	if (repeatThunder == 0)
		repeatThunder = 1;
	for(count = 0; count <= repeatThunder; count++) {
		setAllLeds(red0, green0, blue0, white0);
		for(count = 0; count < random(15, 50); count++) {
			leds[Pixel + count] = CRGBW(red1, green1, blue1, white1);
			// delay(random(2));
			if (count == LED_COUNT - 1) {
				break;
			}
		}
		stripShow();
		delay(SparkleDelay);
		for(count = 0; count < random(50); count++) {
			leds[Pixel + count] = CRGBW(red0, green0, blue0, white0);
			// delay(random(2));
			if (count == LED_COUNT - 1) {
				break;
			}
		}
		FastLED.show();
		//stripShow();
		delay(random(300));
	}
	setAllLeds(red0, green0, blue0, white0);
	if (random(1) == 1) {
		thunderstorm(red0, green0, blue0, white0, red1, green1, blue1, white1, SparkleDelay, SpeedDelay);
	}
	else {
		delay(SpeedDelay);
	}
}

void	simpleChase(t_all_data allData, int r, int g, int b, int w, int speedDelay) {
	int count;
	for(count = 0; count < LED_COUNT; count++) {
		leds[count] = CRGBW(r, g, b, w);
		delay(speedDelay);
	}
	for(count = 0; count < LED_COUNT; count++) {
		leds[count] = CRGBW(0, 0, 0, 0);
		delay(speedDelay);
	}
}

void	colorTransitionAllStrip(byte red0, byte green0, byte blue0, byte white0, byte red1, byte green1, byte blue1, byte white1, int speed, int indexLed) {
	int n = 50;
	int	strip = 0;
	int	Rnew;
	int	Gnew;
	int	Bnew;
	int	Wnew;

	for (int i = 0; i <= n; i++)
	{
		Rnew = red0 + (red1 - red0) * i / n;
		Gnew = green0 + (green1 - green0) * i / n;
		Bnew = blue0 + (blue1 - blue0) * i / n;
		Wnew = white0 + (white1 - white0) * i / n;
		strip = 0;
		while (strip < 6) {
			if (strip % 2 == 0)
				leds[indexLed + (LED_COUNT/6) * strip] = CRGBW(Rnew, Gnew, Bnew, Wnew);
				// setPixel(indexLed + (LED_COUNT/6) * strip, Rnew, Gnew, Bnew, Wnew);
			else
				leds[(LED_COUNT/6) * (strip + 1) - indexLed - 1] = CRGBW(Rnew, Gnew, Bnew, Wnew);
				// setPixel((LED_COUNT/6) * (strip + 1) - indexLed - 1, Rnew, Gnew, Bnew, Wnew);
			strip++;
		}
		delay(speed/n);
		FastLED.show();
	}
}

void	sunSimulation(byte red0, byte green0, byte blue0, byte white0, byte red1, byte green1, byte blue1, byte white1, int speed) {
	int countLed = 0;

	setAllLeds(red0, green0, blue0, white0);
	Serial.println("\n\n\nin sunSimulation()");
	while(countLed < LED_COUNT/6) {
		Serial.print("Led ");
		Serial.println(countLed);
		colorTransitionAllStrip(red0, green0, blue0, white0, red1, green1, blue1, white1, speed/(LED_COUNT/6), countLed);
		countLed++;
	}
}






// void fadeToBlack(int ledNo, byte fadeValue) {
//  #ifdef ADAFRUIT_NEOPIXEL_H
// 	// NeoPixel
// 	colorRgbw rgbw;
// 	uint32_t oldColor;
// 	uint8_t r, g, b;

// 	oldColor = strip.getPixelColor(ledNo);
// 	r = (oldColor & 0x00ff0000UL) >> 16;
// 	g = (oldColor & 0x0000ff00UL) >> 8;
// 	b = (oldColor & 0x000000ffUL);

// 	r=(r<=10)? 0 : (int) r-(r*fadeValue/256);
// 	g=(g<=10)? 0 : (int) g-(g*fadeValue/256);
// 	b=(b<=10)? 0 : (int) b-(b*fadeValue/256);
// 	rgbw = rgbToRgbw(r, g, b);
// 	setPixel(ledNo, rgbw.red, rgbw.green, rgbw.blue, rgbw.white);
//  #endif
//  #ifndef ADAFRUIT_NEOPIXEL_H
//    // FastLED
//    leds[ledNo].fadeToBlackBy( fadeValue );
//  #endif  
// }

// void	meteorRain(byte red, byte green, byte blue, byte white, byte meteorSize, byte meteorTrailDecay, boolean meteorRandomDecay, int SpeedDelay) {	
// 	colorRgbw rgbw;
// 	setAllLeds(0, 0, 0, 0);
	
// 	for(int i = 0; i < LED_COUNT + LED_COUNT; i++) {   
// 		for(int j=0; j<LED_COUNT; j++) {
// 			if( (!meteorRandomDecay) || (random(10)>5) ) {
// 				fadeToBlack(j, meteorTrailDecay);        
// 			}
// 		}
	
// 		for(int j = 0; j < meteorSize; j++) {
// 			if((i -  j <LED_COUNT) && (i - j>=0) ) {
// 				rgbw = rgbToRgbw(red, green, blue);
// 				setPixel(i - j, rgbw.red, rgbw.green, rgbw.blue, rgbw.white);
// 			}
// 		}
	
// 		stripShow();
// 		delay(SpeedDelay);
// 	}
// }
