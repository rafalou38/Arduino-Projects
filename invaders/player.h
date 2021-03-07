#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "consts.h"
#include "leds.h"
#include "joystick.h"

int pos_x = 0;
int angle_y = 0;

void drawPlayer()
{
	angle_y = get_y();

	if (angle_y != 0)
	{
		pos_x -= min(1, max(-1, angle_y));
	}

	if (digitalRead(MODE_SW))
	{
		if (pos_x < 0)
		{
			pos_x = GRID_WIDTH + pos_x;
		}

		pos_x = pos_x % GRID_WIDTH;
	}

	pos_x = min(GRID_WIDTH - 1, max(0, pos_x));

	leds.set_one(pos_x % GRID_WIDTH, GRID_HEIGHT - 1, leds.color(0, 0, 255));
}

#endif