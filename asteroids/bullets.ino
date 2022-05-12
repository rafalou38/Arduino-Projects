#include "bullets.h"

bullet::bullet()
{
	x = 0;
	y = 0;
	alive = false;
}

void bullet::show_debug()
{
	Serial.print("bullet ");
	Serial.print(" x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" alive: ");
	Serial.println(alive);
}
void bullet::show_debug(byte i)
{
	Serial.print("bullet: ");
	Serial.print(i);
	Serial.print(" x: ");
	Serial.print(x);
	Serial.print(" y: ");
	Serial.print(y);
	Serial.print(" alive: ");
	Serial.println(alive);
}

void bullet::update()
{
	if (alive)
	{
		x += BULLETS_SPEED;
		if (x >= GRID_WIDTH)
		{
			alive = false;
		}
	}
}
void bullet::draw()
{
	leds.set_one(min(floor(x), GRID_WIDTH - 1), floor(y), BULLET_COLOR);
}
void bullet::init()
{
	x = 0;
	y = player_pos_y;
	alive = true;
}