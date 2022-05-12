#ifndef DEF_consts
#define DEF_consts

// leds grid
#define LED_PIN 6
#define GRID_WIDTH 8
#define GRID_HEIGHT 4

// games vars
#define MAX_BULLETS 10
#define MAX_ASTEROIDS 10
#define ASTEROIDS_MIN_SPEED 0.05
#define ASTEROIDS_MAX_SPEED 0.3
#define BULLETS_SPEED 0.2
#define PLAYER_SPEED 0.05

#define MODE_SW 3

// joystick vars
#define JOY_PIN_X A1
#define JOY_PIN_Y A0
#define JOY_PIN_SW 2
#define DEADZONE 10

// colors
#define RED leds.color(219, 31, 31, 0.1)
#define BLUE leds.color(19, 145, 235, 0.1)
#define BULLET_COLOR leds.color(219, 26, 206, 0.1)

// global vars
bool game_is_on = 1;

#endif