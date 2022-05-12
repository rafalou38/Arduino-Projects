#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(16, 6, NEO_GRB + NEO_KHZ800);

int initX, initY, goalIndex, cursorIndex;
unsigned long goalStartTime, goalEndTime;

#define bucket 25

void setup()
{
	Serial.begin(9600);

	strip.begin();
	strip.show();

	analogReference(EXTERNAL);

	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);

	initX = analogRead(A0);
	initY = analogRead(A1);

	randomSeed(analogRead(A2));

	goalIndex = random(15);
	goalStartTime = millis();
}

void setNthPixel(int pixel, uint32_t color)
{
	if (pixel <= 3)
		strip.setPixelColor(pixel, color);
	else if (pixel <= 7)
		strip.setPixelColor(11 - pixel, color);
	else if (pixel <= 11)
		strip.setPixelColor(pixel, color);
	else if (pixel <= 15)
		strip.setPixelColor(27 - pixel, color);
}

int getCursorIndex()
{
	int x, y, xOffset, yOffset;

	xOffset = initX - 2 * bucket;
	yOffset = initY - 2 * bucket;

	x = (analogRead(A0) - xOffset) / bucket;
	y = (analogRead(A1) - yOffset) / bucket;

	Serial.print("x:");
	Serial.print(x);
	Serial.print(" y:");
	Serial.println(y);

	if (x < 0 || x > 3 || y < 0 || y > 3)
		return -1;
	else
		return x * 4 + y;
}

void loop()
{
	cursorIndex = getCursorIndex();

	for (int i = 0; i < 16; i++)
	{
		strip.setPixelColor(i, strip.Color(0, 0, 0));
	}

	setNthPixel(goalIndex, strip.Color(0, 0, 20));

	if (cursorIndex != -1)
		setNthPixel(cursorIndex, strip.Color(0, 20, 0));

	if (cursorIndex == goalIndex)
		setNthPixel(cursorIndex, strip.Color(0, 10, 10));
	else
		goalStartTime = millis();

	if (millis() - goalStartTime >= 1500)
	{
		goalIndex = random(15);
		goalStartTime = millis();
	}

	strip.show();
}
