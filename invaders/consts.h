#ifndef DEF_consts
#define DEF_consts

#define LED_PIN 6
#define GRID_WIDTH 8
#define GRID_HEIGHT 4

#define MAX_ENEMIES 10
#define ENEMIES_MIN_SPEED 0.05
#define ENEMIES_MAX_SPEED 0.3

#define MODE_SW 2

#define JOY_PIN_X A1
#define JOY_PIN_Y A0
#define JOY_PIN_SW 4
#define DEADZONE 50

#define RED leds.color(219, 31, 31, 0.1)
#define BLUE leds.color(19, 145, 235, 0.1)

bool game_is_on = 1;

#endif