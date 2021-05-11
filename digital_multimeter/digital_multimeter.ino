#include "LiquidCrystal.h"

#define VR1 4700
#define VR2 15000

#define RR2 15000

#define VOLTMETER A0
#define OHMMETER A1
#define BUTTON 2

#define BACKLIGHT 6

#define MODE_VOLT 0
#define MODE_RES_1K 1

int mode = MODE_VOLT;
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

byte ohm[8] = {
		0b00000,
		0b01110,
		0b10001,
		0b10001,
		0b10001,
		0b01010,
		0b11011,
		0b00000,
};

double calculateVoltage()
{
	double vout, vin, ratio;
	vout = 5 * analogRead(VOLTMETER) / (double)1024;

	ratio = VR1 / (double)(VR1 + VR2);
	vin = vout / ratio;

	return vin;
}

long calculateResistance()
{
	double vout, numerator, denominator;

	vout = 5 * analogRead(OHMMETER) / (double)1024;

	numerator = vout * RR2;
	denominator = 8 - vout;

	if (analogRead(OHMMETER) > 1000)
		return -1;
	else
		return numerator / denominator;
}

void switchMode()
{
	mode = (mode + 1) % 2;
}

void setup()
{
	pinMode(VOLTMETER, INPUT);
	pinMode(OHMMETER, INPUT);

	lcd.begin(16, 2);
	lcd.createChar(0, ohm);

	attachInterrupt(digitalPinToInterrupt(BUTTON), switchMode, RISING);
}

void loop()
{
	analogWrite(BACKLIGHT, 100);

	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Mode:");

	lcd.setCursor(0, 2);
	lcd.print("value:");
	if (mode == MODE_RES_1K)
	{
		lcd.setCursor(6, 0);
		lcd.print("Resistance");
		lcd.setCursor(7, 2);
		int resistance = calculateResistance();
		if (resistance == -1)
			lcd.print("OL");
		else
		{
			lcd.print(resistance);
			lcd.write(byte(0));
		}
	}
	else if (mode == MODE_VOLT)
	{
		lcd.setCursor(6, 0);
		lcd.print("Voltage");
		lcd.setCursor(7, 2);
		lcd.print(calculateVoltage());
		lcd.print("v");
	}
	delay(250);
}
