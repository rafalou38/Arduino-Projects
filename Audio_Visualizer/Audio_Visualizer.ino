#include <Adafruit_NeoPixel.h>

#define LEDPIN 6
#define MICPIN A1
#define POTENTIOMETER A0
#define MIN_SOUND 600

uint32_t ledColorArray[8];
uint32_t color;
int potentiometer;
float brightness = 0.25;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LEDPIN, NEO_GRB + NEO_KHZ800);
int sound;

void turn_on(int strength)
{
	Serial.println(strength);
	for (int i = 0; i < map(strength, 0, 50, 0, 8); i++)
	{
		// map(i, 0, 8, 0, 25535)
		// Serial.println(map(i, 0, 8, 0, 65535));
		color = leds.ColorHSV(
			map(i, 0, 8, 0, 65535),
			255,
			255);

		ledColorArray[i] = color;
	}
	// Serial.println();
}
void turn_off()
{
	bool complete = false;
	for (int i = 7; i >= 0 && !complete; i--)
	{
		if (ledColorArray[i] != 0)
		{
			delay(100);
			ledColorArray[i] = 0;
			complete = true;
		}
	}
}

void setup()
{
	Serial.begin(9600);
	leds.begin();
	leds.show();

	pinMode(MICPIN, INPUT_PULLUP);
	pinMode(POTENTIOMETER, INPUT);

	// attachInterrupt(digitalPinToInterrupt(MICPIN), turn_on, RISING);
}

void loop()
{
	for (int i = 0; i < 8; i++)
	{
		leds.setPixelColor(4 * i, ledColorArray[i]);
		leds.setPixelColor(4 * i + 1, ledColorArray[i]);
		leds.setPixelColor(4 * i + 2, ledColorArray[i]);
		leds.setPixelColor(4 * i + 3, ledColorArray[i]);
	}

	leds.show();
	turn_off();
	sound = analogRead(MICPIN);
	// potentiometer = analogRead(POTENTIOMETER);
	if (sound > MIN_SOUND)
	{
		turn_on(sound - MIN_SOUND);
	}

	// Serial.println(sound);
	// if (potentiometer < 341)
	// {
	// 	color = leds.Color(
	// 		0,
	// 		map(potentiometer, 0, 340, 255, 0) * brightness,
	// 		map(potentiometer, 0, 340, 0, 255) * brightness);
	// }
	// if (potentiometer < 682 && potentiometer >= 341)
	// {
	// 	color = leds.Color(
	// 		0,
	// 		map(potentiometer, 341, 681, 255, 0) * brightness,
	// 		map(potentiometer, 341, 681, 0, 255) * brightness);
	// }
	// if (potentiometer >= 682)
	// {
	// 	color = leds.Color(
	// 		0,
	// 		map(potentiometer, 682, 1023, 0, 255) * brightness,
	// 		map(potentiometer, 682, 1023, 255, 0) * brightness);
	// }
}
