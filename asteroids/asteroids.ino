#include "leds.h"
#include "consts.h"

#include "player.h"
#include "bullets.h"

uint32_t lose_red = leds.color(236, 28, 36, 0.2);
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

bullet bullets[MAX_BULLETS];

int frames_cnt = 0;
int s = 0;
void shoot()
{
	Serial.print("shoot! ");
	Serial.println(s);
	s++;
	for (byte i = 0; i < MAX_BULLETS; i++)
	{
		if (!bullets[i].alive)
		{
			bullets[i].init();
			break;
			delay(100);
		}
	}
}

void setup()
{
	Serial.begin(9600);
	Serial.println("-------------START-------------");

	randomSeed(analogRead(A5));

	leds.setup_leds();
	leds.turn_off();

	pinMode(JOY_PIN_SW, INPUT_PULLUP);

	attachInterrupt(digitalPinToInterrupt(JOY_PIN_SW), shoot, FALLING);
	// for (byte i = 0; i < MAX_BULLETS; i++)
	// {
	// 	bullets[i] = bullet();
	// }
}

void loop()
{
	delay(10);
	// Serial.println("loop");
	leds.turn_off();

	updatePlayer();
	drawPlayer();

	for (byte i = 0; i < MAX_BULLETS; i++)
	{
		// bullets[i].show_debug(i);
		if (bullets[i].alive)
		{
			bullets[i].update();
			bullets[i].draw();
		}
	}

	// // updateBullets();
	// // drawBullets();

	// else if (game_is_on)
	// {
	// 	drawPlayer();
	// 	drawEnemies();
	// }
	// else
	// {
	// 	leds.draw(END_MSG);
	// }

	leds.update();
}
