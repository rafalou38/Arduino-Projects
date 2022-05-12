#include <Servo.h>
#include "HX711.h"

#include "leds.h"

#define CALIBRATION_FACTOR -150000

#define SCK_PIN 0
#define DT_PIN 1
#define SERVO_PIN 2

HX711 scale(DT_PIN, SCK_PIN);

Servo servo;
int angle = 0;
int n = 0;

uint32_t ledColorArray[4 * 8];
float brightness = 0.25;

void setup()
{
    scale.set_scale(CALIBRATION_FACTOR);
    scale.tare();

    servo.attach(SERVO_PIN);

    leds.setup_leds();
}
int i = 0;
void loop()
{
    angle = map(scale.get_units(), 0, 8, 180, 15);

    servo.write(angle);

    n = map(scale.get_units(), 0, 8, 0, GRID_HEIGHT * GRID_WIDTH);
    for (size_t i = 0; i < GRID_HEIGHT * GRID_WIDTH; i++)
    {
        if (i < n)
        {
            leds.set_one(i,
                         leds.color(
                             map(i, 0, GRID_HEIGHT * GRID_WIDTH, 255, 0),
                             map(i, 0, GRID_HEIGHT * GRID_WIDTH, 0, 255),
                             0));
        }
        else
        {
            leds.set_one(i, 0);
        }
    }
    leds.update();
    // delay(500);
}