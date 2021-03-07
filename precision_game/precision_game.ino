// #include <Adafruit_NeoPixel.h>

// #define LED_PIN 6
// #define GRID_WIDTH 8
// #define GRID_HEIGHT 4

// Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LED_PIN, NEO_GRB + NEO_KHZ800);
#include "leds.h"

#define POT_PIN A2
#define JOY_PIN_X A1
#define JOY_PIN_Y A0

int color_bg = leds.color(122, 233, 255, 0.05);
int color_target = leds.color(216, 255, 77, 0.25);

int angle_x = 0;
int angle_y = 0;

int pos_x = 0;
int pos_y = 0;

int convJoy(int raw, int deadZone = 10, int min = -100, int max = 100)
{
	int v = map(raw, 0, 1023, min, max);
	if (abs(v) < deadZone)
	{
		v = 0;
	}

	return v;
}

void setup()
{
	Serial.begin(9600);

	pinMode(A3, INPUT);
	leds.setup_leds();
	leds.turn_off();
}

void loop()
{
	delay(map(analogRead(POT_PIN), 0, 1023, 0, 500));
	angle_x = convJoy(analogRead(JOY_PIN_X));
	angle_y = convJoy(analogRead(JOY_PIN_Y));

	if (angle_x != 0)
	{
		pos_y += min(1, max(-1, angle_x));
	}
	if (angle_y != 0)
	{
		pos_x -= min(1, max(-1, angle_y));
	}

	leds.turn_off();

	leds.set_one(pos_x % GRID_WIDTH, pos_y % GRID_HEIGHT, leds.color(0, 0, 255));
	leds.update();
}
