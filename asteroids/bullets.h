#ifndef DEF_ENEMY
#define DEF_ENEMY

#include "consts.h"
#include "player.h"
#include "leds.h"

class bullet
{
public:
	bullet();
	void show_debug();
	void show_debug(byte i);
	void update();
	void draw();
	void init();

	bool alive;

private:
	float x;
	float y;
};


#endif