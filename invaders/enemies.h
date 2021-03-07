#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "consts.h"
#include "player.h"
#include "util.h"

float enemies[MAX_ENEMIES][2] = {};
float enemies_cnt = 1;

void setupEnemies()
{
	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemies[i][0] = -1;
		enemies[i][1] = -1;
	}
}

void drawEnemies()
{
	enemies_cnt += 0.05;
	for (int i = 0; i < floor(min(enemies_cnt, MAX_ENEMIES)); i++)
	{
		if (floor(enemies[i][0]) == -1)
		{

			enemies[i][0] = (int)random(GRID_WIDTH);
			enemies[i][1] = 0;
		}
		else if (floor(enemies[i][1]) == GRID_HEIGHT - 1)
		{
			if (pos_x == enemies[i][0])
			{
				loose();
			}
			enemies[i][0] = -1;
			enemies[i][1] = -1;
		}
		else
		{
			enemies[i][1] += random(ENEMIES_MIN_SPEED * 10, ENEMIES_MAX_SPEED * 10 + 1) / 10.0;
			leds.set_one(floor(enemies[i][0]), floor(enemies[i][1]), RED);
		}
	}
}

#endif