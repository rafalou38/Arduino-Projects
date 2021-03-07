#ifndef DEF_JOYSTICK
#define DEF_JOYSTICK

#include "consts.h"

int convJoy(int raw, int min = -100, int max = 100)
{
	int v = map(raw, 0, 1023, min, max);
	if (abs(v) < DEADZONE)
	{
		v = 0;
	}

	return v;
}

int get_x()
{
	return convJoy(analogRead(JOY_PIN_X));
}
int get_y()
{
	return convJoy(analogRead(JOY_PIN_Y));
}

bool buttonPressed()
{
	return !digitalRead(JOY_PIN_SW);
}
#endif