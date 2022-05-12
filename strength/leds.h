#ifndef DEF_LEDS
#define DEF_LEDS

#include "consts.h"
#include <Adafruit_NeoPixel.h>

class _leds
{
public:
	uint32_t color(uint8_t r, uint8_t g, uint8_t b);
	uint32_t color(uint8_t r, uint8_t g, uint8_t b, float brightness);

	void turn_off();

	void set_all(uint32_t color);

	void set_one(int n, uint32_t color);
	void set_one(int x, int y, uint32_t color);

	void set_row(int row, uint32_t color);

	void update(void);
	void setup_leds();
	void draw(uint32_t figure[GRID_HEIGHT * GRID_WIDTH]);

private:
	Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LED_PIN, NEO_GRB + NEO_KHZ800);

	uint32_t ledColorArray[GRID_HEIGHT * GRID_WIDTH];
	float brightness = 0.25;

	bool has_changed = 1;
};

_leds leds;
#endif