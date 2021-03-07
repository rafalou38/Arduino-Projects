#include "leds.h"

#ifndef my_leds
#define my_leds
uint32_t _leds::color(uint8_t r, uint8_t g, uint8_t b, float brightness)
{
	return leds.Color(r * brightness, g * brightness, b * brightness);
}
uint32_t _leds::color(uint8_t r, uint8_t g, uint8_t b)
{
	return leds.Color(r * brightness, g * brightness, b * brightness);
}

void _leds::turn_off(void)
{
	set_all(0);
	has_changed = 1;
}

void _leds::set_all(uint32_t color)
{
	for (int n = 0; n < GRID_HEIGHT * GRID_WIDTH; n++)
	{

		ledColorArray[n] = color;
	}
	// leds.fill(color);
	has_changed = 1;
}

void _leds::set_one(int n, uint32_t color)
{
	ledColorArray[n] = color;

	has_changed = 1;
}
void _leds::set_row(int row, uint32_t color)
{
	for (int i = 0; i < GRID_HEIGHT; i++)
	{
		ledColorArray[row * GRID_HEIGHT + i] = color;
	}

	has_changed = 1;
}
void _leds::set_one(int x, int y, uint32_t color)
{

	while (x < 0)
	{
		x = GRID_WIDTH + x;
	}
	while (y < 0)
	{
		y = GRID_HEIGHT + y;
	}
	int n = x * GRID_HEIGHT + (((x % 2) == 0) ? ((GRID_HEIGHT - y) - 1) : y);

	ledColorArray[n] = color;

	has_changed = 1;
}

void _leds::update(void)
{
	if (has_changed)
	{
		for (int n = 0; n < GRID_HEIGHT * GRID_WIDTH; n++)
		{
			leds.setPixelColor(n, ledColorArray[n]);
		}
		leds.show();
		has_changed = 0;
	}
}

void _leds::draw(uint32_t figure[GRID_HEIGHT * GRID_WIDTH])
{
	for (int i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
	{
		ledColorArray[i] = figure[i];
	}
	has_changed = 1;
}

void _leds::setup_leds()
{
	leds.begin();
	leds.show();
}
#endif