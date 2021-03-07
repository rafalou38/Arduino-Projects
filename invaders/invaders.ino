#include "leds.h"
#include "consts.h"

#include "enemies.h"
#include "player.h"

uint32_t lose_red = leds.color(236, 28, 36, 0.2);
int frames_cnt = 0;
uint32_t END_MSG[]{
	lose_red,
	lose_red,
	lose_red,
	lose_red,
	lose_red,
	0,
	0,
	lose_red,
	lose_red,
	lose_red,
	0,
	lose_red,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	lose_red,
	lose_red,
	lose_red,
	lose_red,
	lose_red,
	0,
	0,
	lose_red,
	lose_red,
	lose_red,
	lose_red,
	lose_red,
};
void setup()
{
	// Serial.begin(9600);

	randomSeed(analogRead(A5));

	leds.setup_leds();
	leds.turn_off();

	pinMode(JOY_PIN_SW, INPUT_PULLUP);
	setupEnemies();
}

void loop()
{
	delay(100);

	leds.turn_off();
	if (buttonPressed())
	{
		game_is_on = 1;
		setupEnemies();
		enemies_cnt = 1;
	}
	else if (game_is_on)
	{
		drawPlayer();
		drawEnemies();
	}
	else
	{
		leds.draw(END_MSG);
	}

	leds.update();
}
