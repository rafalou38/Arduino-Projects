#ifndef DEF_PLAYER
#define DEF_PLAYER

#include "consts.h"
#include "leds.h"
#include "joystick.h"

float player_pos_y = 0;
int angle_y = 0;

void updatePlayer()
{
	angle_y = get_y();

	if (angle_y != 0)
	{
		player_pos_y += min(1, max(-1, angle_y)) * PLAYER_SPEED;
	}

	player_pos_y = min(GRID_HEIGHT - 1, max(0, player_pos_y));
}

void drawPlayer()
{
	leds.set_one(0, floor(player_pos_y), leds.color(0, 0, 255));
}



#endif