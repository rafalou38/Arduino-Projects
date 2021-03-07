#ifndef DEF_UTIL
#define DEF_UTIL

#include "leds.h"
#include "consts.h"

#include "enemies.h"
#include "player.h"

void loose()
{
	for (int i = 0; i < 5; i++)
	{
		/* code */
		leds.turn_off();
		leds.set_one(pos_x, GRID_HEIGHT - 1, leds.color(255, 0, 0));
		leds.update();
		delay(50);
		leds.turn_off();
		leds.update();
		delay(50);
	}
	game_is_on = 0;
}
#endif