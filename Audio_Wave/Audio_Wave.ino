#include <Adafruit_NeoPixel.h>

#define LEDPIN 6
#define MICPIN A1
#define POTENTIOMETER A0
#define MIN_SOUND 700
#define SEGMENT_STRENGTH 5

uint32_t ledColorArray[8];
uint32_t color;
float brightness = 0.25;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LEDPIN, NEO_GRB + NEO_KHZ800);
int sound;

void turn_on(int strength)
{
	for (int i = 0; i < 8; i++)
	{
		if (i < strength)
		{
			color = leds.ColorHSV(
				map(i, 0, 8, 0, 65535),
				255,
				255);
		}
		else
		{
			color = 0;
		}

		ledColorArray[i] = color;
	}
}
void turn_off()
{
	for (int i = 0; i < 8; i++)
	{
		ledColorArray[i] = 0;
	}
}

void setup()
{
	Serial.begin(9600);
	leds.begin();
	leds.show();

	pinMode(MICPIN, INPUT_PULLUP);
	pinMode(POTENTIOMETER, INPUT);
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

	sound = analogRead(MICPIN);
	Serial.println(sound);
	if (sound >= MIN_SOUND)
	{
		turn_on(round((sound - MIN_SOUND) / SEGMENT_STRENGTH));
	}
	else
	{
		turn_off();
	}
	delay(10);
}
