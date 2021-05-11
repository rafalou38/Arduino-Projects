
#include <Keypad.h>
#include <LiquidCrystal.h>

#define ROWS 4
#define COLS 4

int lightThreshold = 950;
char keyLayout[ROWS][COLS] = {
		{'1', '2', '3', 'a'},
		{'4', '5', '6', 'b'},
		{'7', '8', '9', 'c'},
		{'*', '0', '#', 'd'}};

#define BUZZER A2
#define LDR A1
#define BACKLIGHT A0

byte rowPins[ROWS] = {6, 5, 4, 3};
byte colPins[COLS] = {2, 1, 0, 7};
byte brightness = 100;

char inputList[5];
int inputIndex = 0;
int lastBuz = 0;
int Buz = 0;
String passcode = "1234";
byte curentScreen = 0;
bool unlocked = false;
bool lightLCD = true;
Keypad myKeypad = Keypad(makeKeymap(keyLayout), rowPins, colPins, ROWS, COLS);
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
void drawScreen()
{
	lcd.clear();
	lcd.setCursor(0, 0);
	switch (curentScreen)
	{
	case 0: // code
		lcd.print("Status: ");
		lcd.setCursor(8, 0);
		lcd.print("LOCKED");
		lcd.setCursor(0, 1);
		lcd.print("Passcode: ");
		lcd.print(String(inputList));
		break;
	case 1: // brightness
		lcd.print("brightness: ");
		lcd.print(brightness);
		lcd.print("%");
		break;
	case 2: // brightness
		lcd.print("contrast: ");
		lcd.print(brightness);
		lcd.print("%");
		break;
	case 3: // brightness
		lcd.print("reset pasword");
		lcd.setCursor(0, 1);
		lcd.print("old pass:");
		break;
	default:
		break;
	}
}

void setup()
{
	// Serial.begin(9600);
	lcd.begin(20, 4);
	drawScreen();
	pinMode(BACKLIGHT, OUTPUT);
	pinMode(BUZZER, OUTPUT);
	pinMode(LDR, INPUT);
}

void loop()
{
	char inputKey = myKeypad.getKey();
	if (inputKey)
	{
		switch (inputKey)
		{
		case 'a':
			curentScreen = 0;
			break;
		case 'b':
			curentScreen = 1;
			break;
		case 'c':
			curentScreen = 2;
			break;
		case 'd':
			curentScreen = 3;
			break;
		case '*':
			for (int i = 0; i < 4; i++)
			{
				inputList[i] = 0;
			}
			inputIndex = 0;
			unlocked = false;
			break;
		case '#':
			lightLCD = !lightLCD;
			break;

		default:
			inputList[inputIndex] = inputKey;
			inputIndex++;
			unlocked = false;
			break;
		}

		drawScreen();
		if (inputIndex >= 4)
		{
			inputIndex = 0;
			if (String(inputList) == passcode)
			{
				unlocked = true;
				lcd.setCursor(8, 0);
				lcd.print("UNLOCKED");
				lcd.setCursor(0, 1);
				lcd.print("Press '*' to lock.");
			}
			else
			{
				unlocked = false;
				lcd.setCursor(0, 1);
				lcd.print("Incorrect passcode.");
			}
			for (int i = 0; i < 4; i++)
			{
				inputList[i] = 0;
			}
		}
	}
	// Serial.println(analogRead(LDR));

	if (!unlocked && analogRead(LDR) < lightThreshold)
	{
		int delay = 200;
		if (millis() - lastBuz > delay)
		{
			Buz++;
			if (Buz % 2)
			{

				tone(BUZZER, 1000, delay);
			}
			else
			{
				tone(BUZZER, 950, delay);
			}

			lastBuz = millis();
		}
	}
	else
	{
		// digitalWrite(BUZZER, LOW);
	}

	if (lightLCD)
	{
		digitalWrite(BACKLIGHT, HIGH);
	}
	else
	{
		digitalWrite(BACKLIGHT, LOW);
	}
}