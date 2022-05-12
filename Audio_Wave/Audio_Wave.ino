#include <Adafruit_NeoPixel.h>

#define LEDPIN 6
#define MICPIN 2
#define POTENTIOMETER A0
#define MIN_SOUND 700
#define SEGMENT_STRENGTH 5

float brightness = 0.25;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(32, LEDPIN, NEO_GRB + NEO_KHZ800);
int sound;
int wait = 50;
bool cycle = false;

void set_row(byte row, uint32_t color)
{
	leds.setPixelColor(4 * row, color);
	leds.setPixelColor(4 * row + 1, color);
	leds.setPixelColor(4 * row + 2, color);
	leds.setPixelColor(4 * row + 3, color);
}

void turn_on()
{
	if (!cycle)
	{
		Serial.println("turn on");

		for (int i = 0; i < 8; i++)
		{
			cycle = true;
			set_row(i, leds.ColorHSV(
										 map(i, 0, 8, 0, 65535),
										 255,
										 255));
			delay(wait);
			leds.show();
		}
		turn_off();
		delay(500);
		cycle = false;
		Serial.println("end turn on");
	}
}
void turn_off()
{
	// for (int i = 8; i >= 0; i--)
	// {
	// 	set_row(i, 0);
	// 	delay(wait);
	// 	leds.show();
	// }
	for (int i = 0; i < 8; i++)
	{
		set_row(i, 0);
		delay(wait);
		leds.show();
	}
}

void test()
{
	Serial.println("sjgodjfoifj");
}

void setup()
{
	Serial.begin(9600);
	leds.begin();
	leds.show();
	leds.setBrightness(100);
	pinMode(MICPIN, INPUT_PULLUP);
	pinMode(POTENTIOMETER, INPUT);
	attachInterrupt(digitalPinToInterrupt(MICPIN), turn_on, RISING);
}

void loop()
{

	sound = digitalRead(MICPIN);
	// Serial.println(sound);
}
